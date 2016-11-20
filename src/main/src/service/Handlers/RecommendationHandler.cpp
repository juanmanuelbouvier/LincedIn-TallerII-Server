#include <services/Handlers/RecommendationHandler.h>
#include <model/User.h>
#include <model/Recommendation.h>
#include <utils/JSONUtils.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>


HTTPResponse* handle(HTTPRequest* request) {
	map<string,string> path = PathUtils::routerParser(request->getURI(),"/recommendation/:user_id");
	string user_id = path["user_id"];
	if ( !User::exist(user_id) ) {
		return ResponseBuilder::createErrorResponse(404,"INVALID USER");
	}

	if ( request->isGET() ) {
		Json::Value recomendations = Recommendation::getArrayRecommendation(user_id);
		return ResponseBuilder::createJsonResponse(200,recomendations);
	}

	string token = request->getFromHeader("Authorization");
	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(401,"PERMISSION DENIED");
	}

	string user_id_auth = TokenUtils::userIDByToken(token);

	if ( request->isPOST() ) {
		Json::Value body = JSONUtils::stringToJSON( request->getBody() );

		ErrorMessage error = Recommendation::addRecommendation(user_id,user_id_auth, body["description"].asString() );
		if (error) {
			return ResponseBuilder::createErrorResponse(402,error.summary(),2);
		}
		return ResponseBuilder::createOKResponse(200,"RECOMMENDATION SENT");

	}

	if ( request->isDELETE() ) {
		//TODO: Wait method
		ErrorMessage error = Recommendation::removeRecommendation(user_id,user_id_auth);
		if (error) {
			return ResponseBuilder::createErrorResponse(402,error.summary(),2);
		}
		return ResponseBuilder::createOKResponse(200,"RECOMMENDATION DELETED");
	}
	return ResponseBuilder::createErrorResponse(400,"BAD REQUEST");
}

