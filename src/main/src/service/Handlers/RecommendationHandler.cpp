#include <services/Handlers/RecommendationHandler.h>
#include <model/User.h>
#include <model/Recommendation.h>
#include <utils/JSONUtils.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <services/HTTP/HTTPResponseConstants.h>
#include <services/Firebase/FirebaseClient.h>

HTTPResponse* RecommendationHandler::handle(HTTPRequest* request) {

	bool auth = false;
	string user_id_auth = "";
	string token = request->getFromHeader("Authorization");
	if ( TokenUtils::isValidToken(token) ) {
		auth = true;
		user_id_auth = TokenUtils::userIDByToken(token);
	}

	if (PathUtils::matchPathRegexp(request->getURI(),"/recommendations") and request->isGET()){
		if (auth){
			Json::Value recomendations = Recommendation::getArraySentRecommendations(user_id_auth);
			return ResponseBuilder::createJsonResponse(CODE_OK,recomendations);
		}else {
			return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
		}
	}

	map<string,string> path = PathUtils::routerParser(request->getURI(),"/recommendations/:user_id");
	string user_id = path["user_id"];
	if ( !User::exist(user_id) ) {
		return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"INVALID USER");
	}


	if ( request->isGET() ) {
		Json::Value recomendations = Recommendation::getArrayReceivedRecommendations(user_id);
		return ResponseBuilder::createJsonResponse(CODE_OK,recomendations);
	}

	if ( !auth ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
	}

	if ( request->isPOST() ) {
		Json::Value body = JSONUtils::stringToJSON( request->getBody() );

		ErrorMessage error = Recommendation::addRecommendation(user_id,user_id_auth, body["description"].asString() );
		if (error) {
			return ResponseBuilder::createErrorResponse(CODE_ALREADY_EXIST,error.summary());
		}

		string firebase_id = User::getFirebaseID(user_id);
		FirebaseClient::sendNotifications(firebase_id,user_id_auth + " te ha recomendado.",user_id_auth + ": " + body["description"].asString());
		return ResponseBuilder::createEmptyResponse(CODE_OK,"RECOMMENDATION SENT");

	}

	if ( request->isDELETE() ) {
		ErrorMessage error = Recommendation::removeRecommendation(user_id,user_id_auth);
		if (error) {
			return ResponseBuilder::createErrorResponse(CODE_ACCEPTED,error.summary(),CODE_ACCEPTED);
		}
		return ResponseBuilder::createEmptyResponse(CODE_OK,"RECOMMENDATION DELETED");
	}
	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}

