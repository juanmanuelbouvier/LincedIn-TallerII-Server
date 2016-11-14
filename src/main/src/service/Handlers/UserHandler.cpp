#include <services/Handlers/UserHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <model/User.h>
#include <exception/UserException.h>
#include <string>

using namespace std;

UserHandler::UserHandler() {
}

HTTPResponse* UserHandler::handle(HTTPRequest* http_request){

	string method = http_request->getMethod();
	string query = http_request->getQuery();
	
	map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/user/:user_id");

	if (method == "GET"){
		string user_id = path["user_id"];

		//pidió su perfil
		if (user_id == "me"){

			Json::FastWriter writer;
			writer.omitEndingLineFeed();
			string toReturn = writer.write(_createUser("Tu usuario"));

			return ResponseBuilder::createJsonResponse(200,toReturn);

		} else if (User::exist(user_id)){
			//si pidió un usuario que está en la base de datos

			Json::FastWriter writer;
			writer.omitEndingLineFeed();
			string toReturn = writer.write(_createUser(path["user_id"]));

			return ResponseBuilder::createJsonResponse(200,toReturn);
		} else {
			//no hay usuario

			Json::Value error;
			error["Error"] = "Usuario inexistente";
			Json::FastWriter writer;
			writer.omitEndingLineFeed();
			string toReturn = writer.write(error);

			return ResponseBuilder::createJsonResponse(400, toReturn);
		}

	} else if (method == "PUT"){

		return ResponseBuilder::createErrorResponse(500,"BAD REQUEST");

	} else if (method == "DELETE"){

		if (User::deleteUser( path["user_id"])){
			return ResponseBuilder::createErrorResponse(200, "Perfil eliminado");
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

UserHandler::~UserHandler(){
}
