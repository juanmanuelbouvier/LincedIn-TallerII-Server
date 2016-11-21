#include <services/Handlers/GeolocalizationHandler.h>
#include <utils/PathUtils.h>
#include <utils/JSONUtils.h>
#include <utils/TokenUtils.h>
#include <model/Geolocalization.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <services/HTTP/HTTPResponseConstants.h>

HTTPResponse* findNear(HTTPRequest* request) {
	//TODO: Method
	Json::Value queryData = JSONUtils::queryToJson( request->getQuery() );
	Json::Value found = Geolocalization::findUsersByLocation(queryData);
	if (found.isMember("error")) {
		found["parameters"] = queryData;
		return ResponseBuilder::createJsonResponse(CODE_NONEXISTEN,found);
	}
	return ResponseBuilder::createErrorResponse(CODE_OK,"PERMISSION DENIED");
}

HTTPResponse* sendLocation(HTTPRequest* request) {
	Json::Value data = JSONUtils::stringToJSON( request->getBody() );
	string token = request->getFromHeader("Authorization");

	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
	}

	data["user_id"] = TokenUtils::userIDByToken(token);
	if ( Geolocalization::updateLocation(data) ) {
		return ResponseBuilder::createEmptyResponse(CODE_OK,"OK");
	}
	return ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR,"UNEXPECTED ERROR");
}

HTTPResponse* handler(HTTPRequest* request) {
	if ( PathUtils::matchPathRegexp(request->getURI(),"geolocalization/:user_id") ) {
		map<string,string> path = PathUtils::routerParser(request->getURI(),"geolocalization/:user_id");
		string user_id = path["user_id"];
		if (!User::exist(user_id)) {
			ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"INVALID USER");
		}
		Json::Value localization = Geolocalization::getUserLocation(user_id);
		return ResponseBuilder::createJsonResponse(CODE_OK,localization);
	}

	if ( PathUtils::matchPathRegexp(request->getURI(),"geolocalization") ) {
		if ( request->isGET() ) {
			return findNear(request);
		}
		if ( request->isPOST() ) {
			return sendLocation(request);
		}

	}
	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}
