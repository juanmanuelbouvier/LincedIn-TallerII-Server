#include <services/Handlers/LoginHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <model/User.h>
#include <utils/JSONUtils.h>
#include <services/ExternLogin/FacebookAPI.h>
#include <services/Logger/Logger.h>

HTTPResponse* normalLogin(Json::Value data) {
	if ( ( data["email"].isString() || data["user_id"].isString() ) && data["password"].isString() ) {
		string password = data["password"].asString();
		string toVerify = (data["email"].isString()) ? data["email"].asString() : data["user_id"].asString();
		bool isEmailLogin = (data["email"].isString()) ? true : false;
		if (isEmailLogin) {
			//string user_id = User::getIdByEmail( toVerify );
			//if ( user_id.empty() || !User::checkPassword( user_id, password ) ) {
			//	return ResponseBuilder::createErrorResponse(400,"ERROR");
			//}
		} else {
			if ( !User::exist(toVerify) /*|| !User::checkPassword( toVerify, password ) */) {
				return ResponseBuilder::createErrorResponse(400,"ERROR");
			}
		}
		Json::Value responseBody;
		responseBody["description"] = "Hola, " + toVerify;
		//responseBody["token"] = User::generateSessionToken( user_id );
		return ResponseBuilder::createJsonResponse(200,responseBody);
	}
	return ResponseBuilder::createErrorResponse(500,"ERROR");
}

HTTPResponse* facebookLogin(Json::Value data) {
	if ( !data["fb_token"].isString() ) {
		return ResponseBuilder::createErrorResponse(400,"NO_FB_TOKEN");
	}
	string fb_token = data["fb_token"].asString();
	FacebookAPI fb;
	Json::Value fb_data = fb.getInfoFromToken( fb_token );
	Log("Facebook response:\n" + fb_data.toStyledString(),DEBUG);
	if ( fb_data["email"].isString() ) {
		string email = fb_data["email"].asString();
		/* string user_id = User::getIdByEmail( email )
		if ( !user_id.empty() ) {
			Json::Value responseBody;
			responseBody["description"] = "Hola, " + email;
			//responseBody["token"] = User::generateSessionToken( user_id );
			return ResponseBuilder::createJsonResponse(200,responseBody);
		}
		*/
		//Not in database. return all information to register.
		return ResponseBuilder::createJsonResponse(202,fb_data);
	}
	return ResponseBuilder::createErrorResponse(400,"INVALID_FB_TOKEN");
}


HTTPResponse* LoginHandler::handle(HTTPRequest* request) {
	if (!request->isPOST()) {
		return ResponseBuilder::createErrorResponse(400,"ERROR");
	}
	Json::Value bodyJson = JSONUtils::stringToJSON(request->getBody());
	if ( bodyJson["type"].isString() ) {
		if (bodyJson["type"].asString() == "Facebook") {
			Log("Attemp to log in with Facebook",DEBUG);
			return facebookLogin( bodyJson );
		} else {
			Log("Attemp to log in with userid or email and password",DEBUG);
			return normalLogin(bodyJson);
		}
	}
	return ResponseBuilder::createErrorResponse(400,"INVALID_TYPE");
}

