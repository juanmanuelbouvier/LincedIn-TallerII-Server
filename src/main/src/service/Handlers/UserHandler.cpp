#include <services/Handlers/UserHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
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

	if (method == "GET"){

		//pidió su perfil
		if (user_id == "me"){

			Json::Value res = _createUser("Tu usuario");

			return ResponseBuilder::createJsonResponse(200,res);

		} else if (User::exist(user_id)){
			//si pidió un usuario que está en la base de datos

			Json::Value res = _createUser(path["user_id"]);

			return ResponseBuilder::createJsonResponse(200,res);
		} else {
			//no hay usuario

			Json::Value error;
			error["Error"] = "Usuario inexistente";
			return ResponseBuilder::createJsonResponse(400, error);
		}

	} else if (method == "PUT"){
		Json::Value data ;
		ErrorMessage errorMessage = User::update(user_id,data);
		if (errorMessage.empty()){
			return ResponseBuilder::createOKResponse(200,"Perfil modificado.");
		} else {
			Json::Value error;
			error["Error"] = "Parametros invalidos";
			error["summary"] = errorMessage.summary();
			return ResponseBuilder::createJsonResponse(400,error);
		}

		return ResponseBuilder::createErrorResponse(500,"Unexpected error");

	} else if (method == "DELETE"){

		if (User::delet( user_id)){
			return ResponseBuilder::createOKResponse(200, "Perfil eliminado");
		}

		return ResponseBuilder::createErrorResponse(500, "Unexpected error");

	} else {
		return ResponseBuilder::createErrorResponse(500, "BAD REQUEST");
	}
}

Json::Value UserHandler::_createUser(string user_id) {

	try {
		User user = User(user_id);
		return user.asJSON();
	}catch (UserException& e){
		Json::Value error;
		error["Error"] = e.what();
		return error;
	}
}
