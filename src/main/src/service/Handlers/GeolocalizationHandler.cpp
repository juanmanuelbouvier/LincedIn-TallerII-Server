#include <services/Handlers/GeolocalizationHandler.h>
#include <utils/PathUtils.h>
#include <utils/JSONUtils.h>
#include <utils/TokenUtils.h>
#include <model/Geolocalization.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>

HTTPResponse* findNear(HTTPRequest* request) {
	//TODO: Method
	Json::Value queryData = JSONUtils::queryToJson( request->getQuery() );
	Json::Value found = Geolocalization::findUsersByLocation(queryData);
	if (found.isMember("error")) {
		found["parameters"] = queryData;
		return ResponseBuilder::createJsonResponse(404,found);
	}
	return ResponseBuilder::createErrorResponse(200,"PERMISSION DENIED");
}

HTTPResponse* sendLocation(HTTPRequest* request) {
	Json::Value data = JSONUtils::stringToJSON( request->getBody() );
	string token = request->getFromHeader("Authorization");

	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(401,"PERMISSION DENIED");
	}

	data["user_id"] = TokenUtils::userIDByToken(token);
	if ( Geolocalization::updateLocation(data) ) {
		return ResponseBuilder::createOKResponse(200,"OK");
	}
	return ResponseBuilder::createErrorResponse(500,"UNEXPECTED ERROR");
}

HTTPResponse* handler(HTTPRequest* request) {
	if ( PathUtils::matchPathRegexp(request->getURI(),"geolocalization/:user_id") ) {
		map<string,string> path = PathUtils::routerParser(request->getURI(),"geolocalization/:user_id");
		string user_id = path["user_id"];
		if (!User::exist(user_id)) {
			ResponseBuilder::createErrorResponse(404,"INVALID USER");
		}
		Json::Value localization = Geolocalization::getUserLocation(user_id);
		return ResponseBuilder::createJsonResponse(200,localization);
	}

	if ( PathUtils::matchPathRegexp(request->getURI(),"geolocalization") ) {
		if ( request->isGET() ) {
			return findNear(request);
		}
		if ( request->isPOST() ) {
			return sendLocation(request);
		}

	}
	return ResponseBuilder::createErrorResponse(400,"BAD REQUEST");
}
