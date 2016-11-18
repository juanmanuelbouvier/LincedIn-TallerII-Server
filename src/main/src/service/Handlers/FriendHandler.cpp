#include <services/Handlers/FriendHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <utils/ErrorMessage.h>
#include <model/Friends.h>
#include <extern/json.h>

using namespace std;

HTTPResponse* _actionUser(string method,string source_user_id,string user_destination_id);
HTTPResponse* _friends(string source_user_id);

HTTPResponse* FriendHandler::handle(HTTPRequest* http_request) {

	string token = http_request->getFromHeader("Authorization");
	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(401,"PERMISSION DENIED");
	}
	string user_source_id = TokenUtils::userIDByToken(token);

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/friends/:destination_user_id")){

		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/friends/:destination_user_id");

		return _actionUser(http_request->getMethod(),user_source_id,path["destination_user_id"]);

	} else if (http_request->isGET()) {

		return _friends(user_source_id);

	}


	return ResponseBuilder::createErrorResponse(500,"BAD REQUEST");

}


HTTPResponse* _actionUser(string method,string source_user_id,string user_destination_id){

	if (!User::exist(user_destination_id)){
		return ResponseBuilder::createErrorResponse(404,"Usuario destino inexistente: " + user_destination_id,1);
	}

	if (method == "POST"){

		ErrorMessage error = Friends::add(source_user_id,user_destination_id);

		if (error){
			return ResponseBuilder::createErrorResponse(408,"Usuario ya es parte de la red",2);
		}

		return ResponseBuilder::createOKResponse(200,"Solicitud para agregar a la red enviada");

	} else if (method == "DELETE"){

		ErrorMessage error = Friends::remove(source_user_id,user_destination_id);

		if (error){
			return ResponseBuilder::createErrorResponse(408,"Usuario no es parte de la red",3);
		}

		return ResponseBuilder::createOKResponse(204,"Eliminado de la red");
	}

	return ResponseBuilder::createErrorResponse(400,"BAD REQUEST");

}

HTTPResponse* _friends(string source_user_id){

	Json::Value friends = Friends::listFriends(source_user_id);

	Json::Value metadata;
	metadata["version"] = "0.1";
	metadata["total"] = friends.size();
	metadata["count"] = friends.size();

	Json::Value general;
	general["metadata"] = metadata;
	general["friends"] = friends;

	return ResponseBuilder::createJsonResponse(200,general);

}




