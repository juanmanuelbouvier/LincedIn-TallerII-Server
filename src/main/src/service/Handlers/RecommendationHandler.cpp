#include <services/Handlers/RecommendationHandler.h>
#include <model/User.h>
#include <model/Recommendation.h>
#include <utils/JSONUtils.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <services/HTTP/HTTPResponseConstants.h>


HTTPResponse* handle(HTTPRequest* request) {
	map<string,string> path = PathUtils::routerParser(request->getURI(),"/recommendation/:user_id");
	string user_id = path["user_id"];
	if ( !User::exist(user_id) ) {
		return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"INVALID USER");
	}

	if ( request->isGET() ) {
		Json::Value recomendations = Recommendation::getArrayRecommendation(user_id);
		return ResponseBuilder::createJsonResponse(CODE_OK,recomendations);
	}

	string token = request->getFromHeader("Authorization");
	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
	}

	string user_id_auth = TokenUtils::userIDByToken(token);

	if ( request->isPOST() ) {
		Json::Value body = JSONUtils::stringToJSON( request->getBody() );

		ErrorMessage error = Recommendation::addRecommendation(user_id,user_id_auth, body["description"].asString() );
		if (error) {
			return ResponseBuilder::createErrorResponse(CODE_ALREADY_EXIST,error.summary());
		}
		return ResponseBuilder::createEmptyResponse(CODE_OK,"RECOMMENDATION SENT");

	}

	if ( request->isDELETE() ) {
		//TODO: Wait method
		ErrorMessage error = Recommendation::removeRecommendation(user_id,user_id_auth);
		if (error) {
			return ResponseBuilder::createErrorResponse(CODE_ACCEPTED,error.summary(),CODE_ACCEPTED);
		}
		return ResponseBuilder::createEmptyResponse(CODE_OK,"RECOMMENDATION DELETED");
	}
	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}

