#include <services/Handlers/LoginHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <model/User.h>
#include <utils/JSONUtils.h>
#include <utils/TokenUtils.h>
#include <utils/StringUtils.h>
#include <services/ExternLogin/FacebookAPI.h>
#include <services/Logger/Logger.h>


Json::Value createBody(string user_id) {
	Json::Value responseBody;
	responseBody["message"] = "Hi, " + user_id;
	responseBody["token"] = TokenUtils::generateSessionToken( user_id );
	Log("Token created for \"" + user_id + "\"\n\ttoken: " + responseBody["token"].asString());
	return responseBody;
}

HTTPResponse* normalLogin(Json::Value data) {
	if ( ( data["email"].isString() || data["user_id"].isString() ) && data["password"].isString() ) {
		string password = data["password"].asString();
		string user_id = ( data["email"].isString() ) ? User::getIdByEmail( data["email"].asString() ) : data["user_id"].asString();
		if ( !user_id.empty() && User::exist(user_id) && User::checkPassword(user_id,password) ) {
			return ResponseBuilder::createJsonResponse(200, createBody(user_id) );
		}
		return ResponseBuilder::createErrorResponse(500,"WRONG PASSWORD");
	}
	return ResponseBuilder::createErrorResponse(500,"INVALID DATA");
}

HTTPResponse* createUserFromData( Json::Value fb_data ) {
	Json::Value data;
	data["id"] = "tomi";
	data["first_name"] = fb_data["first_name"].asString() + (fb_data.isMember("middle_name") ? " " + fb_data["middle_name"].asString() : "" );
	data["last_name"] = fb_data["last_name"];
	data["email"] = fb_data["email"];
	data["password"] =  StringUtils::generateRandomPassword();
	//TODO: add default profilepicture.

	ErrorMessage checkErrors = User::check(data);
	if (checkErrors) {
		return ResponseBuilder::createErrorResponse(408,checkErrors.summary());
	}

	//TODO: Other data like birthday, profile, picture?
	User newUser = User::create(data);

	//TODO: need newUser.getId() ===> createBody(  );
	return ResponseBuilder::createJsonResponse(200,createBody(newUser.getID()) );
}

HTTPResponse* facebookLogin(Json::Value data) {
	if ( !data["fb_token"].isString() ) {
		return ResponseBuilder::createErrorResponse(400,"NO_FB_TOKEN");
	}
	string fb_token = data["fb_token"].asString();
	FacebookAPI fb;
	Json::Value fb_data = fb.getInfoFromToken( fb_token );
	Log("Facebook response of token:\n" + fb_data.toStyledString());
	if ( fb_data["email"].isString() ) {
		string email = fb_data["email"].asString();
		string user_id = User::getIdByEmail( email );
		if ( !user_id.empty() ) {
			return ResponseBuilder::createJsonResponse(200, createBody(user_id) );
		}
		Log("User not in LincedIn database. Attemp to create it");
		return createUserFromData(fb_data);

	}
	Log("Invalid Facebook Token");
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

