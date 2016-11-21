#include <services/Handlers/LoginHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <model/User.h>
#include <utils/JSONUtils.h>
#include <utils/TokenUtils.h>
#include <utils/StringUtils.h>
#include <utils/DateUtils.h>
#include <services/ExternLogin/FacebookAPI.h>
#include <services/Logger/Logger.h>
#include <exception/UserException.h>
#include <services/HTTP/HTTPResponseConstants.h>


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
			return ResponseBuilder::createJsonResponse(CODE_OK, createBody(user_id) );
		}
		return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"WRONG PASSWORD");
	}
	return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"INVALID DATA");
}

HTTPResponse* createUser( Json::Value data ) {
	string user_id;
	try {
		User newUser = User::create(data);
		user_id = newUser.getID();
	} catch (UserException& e) {
		Log("LoginHandler.cpp::" + to_string(__LINE__) + ". " + string(e.what()),ERROR);
		ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR, "UNEXPECTED ERROR",10);
	}
	return ResponseBuilder::createJsonResponse(CODE_OK,createBody(user_id));
}

HTTPResponse* createUserFromFacebookData( Json::Value fb_data ) {
	Json::Value data;
	data["id"] = StringUtils::toLowerCase(StringUtils::replace(fb_data["first_name"].asString()," ",""));
	data["first_name"] = fb_data["first_name"].asString() + (fb_data.isMember("middle_name") ? " " + fb_data["middle_name"].asString() : "" );
	data["last_name"] = fb_data["last_name"];
	data["email"] = fb_data["email"];
	bool existBirth = fb_data["birthday"].isConvertibleTo(Json::stringValue);
	Json::Value birth = DateUtils::parseDate(fb_data["birthday"].asString(),FacebookAPI::FB_BirthdayDateFormat);
	data["date_of_birth"] = ( existBirth ) ? birth : Json::nullValue;
	data["password"] =  StringUtils::generateRandomPassword();

	ErrorMessage errors = User::check(data);
	return (errors) ? ResponseBuilder::createErrorResponse(408,errors.summary(),408) : createUser(data);
}

HTTPResponse* facebookLogin(Json::Value data) {
	if ( !data["fb_token"].isString() ) {
		return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"NO_FB_TOKEN",400);
	}
	string fb_token = data["fb_token"].asString();
	FacebookAPI fb;
	Json::Value fb_data = fb.getInfoFromToken( fb_token );
	Log("Facebook response of token:\n" + fb_data.toStyledString());
	if ( fb_data["email"].isString() ) {
		string email = fb_data["email"].asString();
		string user_id = User::getIdByEmail( email );
		if ( !user_id.empty() ) {
			return ResponseBuilder::createJsonResponse(CODE_OK, createBody(user_id) );
		}
		Log("User not in LincedIn database. Attemp to create it");
		return createUserFromFacebookData(fb_data);

	}
	Log("Invalid Facebook Token");
	return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"INVALID_FB_TOKEN");
}


HTTPResponse* LoginHandler::handle(HTTPRequest* request) {
	if (!request->isPOST()) {
		return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,"ERROR");
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
	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}

