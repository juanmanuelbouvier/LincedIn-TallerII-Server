#include <services/Handlers/UserHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <utils/ErrorMessage.h>
#include <utils/StringUtils.h>
#include <utils/JSONUtils.h>
#include <model/User.h>
#include <services/Logger/Logger.h>
#include <exception/UserException.h>
#include <string>
#include <services/HTTP/HTTPResponseConstants.h>
#include <services/Firebase/FirebaseClient.h>


using namespace std;

#define SELF_RESERVATED_ID "me"

HTTPResponse* createUserFromData( Json::Value data ) {
	string safeId = ( data.isMember("first_name") ) ? StringUtils::replace( StringUtils::toLowerCase(data["first_name"].asString())," ","") : "user";
	data["id"] = ( data["id"].isString() && data["id"].asString() != SELF_RESERVATED_ID ) ? data["id"].asString() : safeId;

	ErrorMessage error = User::check(data);

	if (error) {
		LOG("Error on create user: " + error.summary(),WARNING);
		return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,error.summary());
	}

	string user_id;

	try {
		User newUser = User::create(data);
		user_id = newUser.getID();
	} catch (UserException& e) {
		Log("UserHandler.cpp::" + to_string(__LINE__) + ". " + string(e.what()),ERROR);
		ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR, "UNEXPECTED ERROR",10);
	}

	Json::Value body;
	body["user_id"] = user_id;
	return ResponseBuilder::createJsonResponse(CODE_OK,body);

}

Json::Value _loadUser(string user_id) {
	try {
		User user = User(user_id);
		return user.asJSON();
	} catch (UserException& e) {
		Json::Value error;
		error["Error"] = "Error on load user.";
		return error;
	}
}

HTTPResponse* getUsers() {
	Json::Value body;
	body["users"] = User::getAllUsers();
	return  ResponseBuilder::createJsonResponse(CODE_OK,body);
}

HTTPResponse* handleProfile(HTTPRequest* http_request) {
	map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/user/:user_id");
	string user_id = path["user_id"];


	string token = http_request->getFromHeader("Authorization");
	bool auth = TokenUtils::isValidToken(token);
	string user_id_auth = (auth) ? TokenUtils::userIDByToken(token) : "";

	if ( http_request->isGET() ){
		if ( SELF_RESERVATED_ID != user_id && !User::exist(user_id)) {
			return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"INVALID USER",CODE_NONEXISTEN);
		}
		if ( SELF_RESERVATED_ID == user_id && !auth ) {
			return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,"PERMISSION DENIED",CODE_PERMISSION_DENIED);
		}
		if (user_id == SELF_RESERVATED_ID && auth) {
			user_id = user_id_auth;
		}
		Json::Value res = _loadUser(user_id);
		return ResponseBuilder::createJsonResponse(CODE_OK,res);
	}

	if ( ( user_id == SELF_RESERVATED_ID && !auth )  || ( user_id != SELF_RESERVATED_ID && user_id != user_id_auth ) ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,"PERMISSION DENIED",CODE_PERMISSION_DENIED);
	}

	user_id = user_id_auth;

	if ( http_request->isPUT() ){

		Json::Value data = JSONUtils::stringToJSON(http_request->getBody());

		if (data.isMember("error")){
			LOG("Error on parse data for update user: " + data["error"].asString(),WARNING);
			return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"INVALID DATA");
		}

		if (!data.isMember("id"))
			data["id"] = user_id;

		ErrorMessage errorMessage = User::update(user_id,data);

		if (errorMessage){
			string error = "Parametros invalidos: " + errorMessage.summary();
			LOG("Error, parameters invalid for update user: " + errorMessage.summary(),WARNING);
			return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,error,CODE_BREACH_PRECONDITIONS);
		}
		return ResponseBuilder::createEmptyResponse(CODE_UPDATE,"UPDATED PROFILE");


	}

	if ( http_request->isDELETE() ){
		if (User::remove(user_id)){
			LOG("User " + user_id + " deleted",INFO);
			ResponseBuilder::createEmptyResponse(CODE_DELETE, "PROFILE DELETED");
		} else {
			LOG("Error on delete user " + user_id ,WARNING);
			ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR, "UNEXPECTED ERROR",CODE_UNEXPECTED_ERROR);
		}
	}
	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST, "BAD REQUEST",CODE_BAD_REQUEST);
}


HTTPResponse* UserHandler::handle(HTTPRequest* http_request){

	if ( PathUtils::matchPathRegexp(http_request->getURI(),"/user/:user_id") ) {
		return handleProfile(http_request);
	}

	if ( PathUtils::matchPathRegexp(http_request->getURI(),"/user")) {
		if (http_request->isPOST()){
			Json::Value data = JSONUtils::stringToJSON( http_request->getBody() );
			if (data.isMember("error")){
				LOG("Error on parse data for add user: " + data["error"].asString(),WARNING);
				return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"Error in data.");
			}

			return createUserFromData(data);

		} else if (http_request->isGET()){
			return getUsers();
		}
	}
	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST, "BAD REQUEST",CODE_BAD_REQUEST);
}
