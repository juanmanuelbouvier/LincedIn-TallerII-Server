#include <services/Handlers/UserHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <utils/ErrorMessage.h>
#include <model/User.h>
#include <exception/UserException.h>
#include <string>

using namespace std;

HTTPResponse* UserHandler::handle(HTTPRequest* http_request){

	string method = http_request->getMethod();
	string query = http_request->getQuery();
	
	map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/user/:user_id");
	string user_id = path["user_id"];

	if (user_id == "me"){
		string token = http_request->getFromHeader("Authorization");
		if ( !TokenUtils::isValidToken(token) ) {
			return ResponseBuilder::createErrorResponse(401,"PERMISSION DENIED");
		}
		user_id = TokenUtils::userIDByToken(token);
	}

	if(!User::exist(user_id)){
		if ((method == "PUT") or (method == "GET") or (method == "DELETE") )
			return ResponseBuilder::createErrorResponse(404, "Usuario inexistente", 1);
	}


	if (method == "GET"){

		Json::Value res = _loadUser(user_id);

		return ResponseBuilder::createJsonResponse(200,res);

	} else if (method == "PUT"){
		Json::Value data ;
		ErrorMessage errorMessage = User::update(user_id,data);

		if (errorMessage){
			string error = "Parametros invalidos: " + errorMessage.summary();

			return ResponseBuilder::createErrorResponse(400,error,2);

		} else {
			return ResponseBuilder::createOKResponse(200,"Perfil modificado.");
		}

	} else if (method == "DELETE"){

		if (User::remove( user_id)){
			return ResponseBuilder::createOKResponse(200, "Perfil eliminado");
		}

		return ResponseBuilder::createErrorResponse(500, "Unexpected error");

	} else {
		return ResponseBuilder::createErrorResponse(500, "BAD REQUEST");
	}
}

Json::Value UserHandler::_loadUser(string user_id) {

	try {
		User user = User(user_id);
		return user.asJSON();
	}catch (UserException& e){
		Json::Value error;
		error["Error"] = "Error on load user.";
		return error;
	}
}
