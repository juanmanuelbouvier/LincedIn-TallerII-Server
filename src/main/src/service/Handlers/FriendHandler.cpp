#include <services/Handlers/FriendHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <utils/ErrorMessage.h>
#include <model/Friends.h>
#include <extern/json.h>
#include <list>
#include <services/HTTP/HTTPResponseConstants.h>
#include <services/Firebase/FirebaseClient.h>

using namespace std;

HTTPResponse* _actionUser(string method,string source_user_id,string user_destination_id);
HTTPResponse* _friends(string source_user_id);
HTTPResponse* _pendingFriends(string user_source_id);
HTTPResponse* _status(string source_user_id,string destination_user_id);

HTTPResponse* FriendHandler::handle(HTTPRequest* http_request) {

	string token = http_request->getFromHeader("Authorization");
	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
	}
	string user_source_id = TokenUtils::userIDByToken(token);

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/friends/:destination_user_id")){

		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/friends/:destination_user_id");

		if ((path["destination_user_id"] == "pending") and http_request->isGET())
			return _pendingFriends(user_source_id);

		return _actionUser(http_request->getMethod(),user_source_id,path["destination_user_id"]);

	} else if (PathUtils::matchPathRegexp(http_request->getURI(),"/friends/status/:user_id") and http_request->isGET()){

		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/friends/status/:user_id");

		return _status(user_source_id,path["user_id"]);

	} else if (http_request->isGET()) {

		return _friends(user_source_id);

	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);

}


HTTPResponse* _status(string source_user_id,string destination_user_id){

	if (!User::exist(destination_user_id)) {
		return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,destination_user_id + " not exist");
	}
	Json::Value body;
	body["status"] = Friends::statusFriend(source_user_id,destination_user_id);

	return ResponseBuilder::createJsonResponse(CODE_OK,body);
}

HTTPResponse* _actionUser(string method,string source_user_id,string user_destination_id){

	if (!User::exist(user_destination_id)){
		return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"Usuario destino inexistente: " + user_destination_id);
	}

	if (method == "POST"){

		ErrorMessage error = Friends::add(source_user_id,user_destination_id);

		if (error){
			return ResponseBuilder::createErrorResponse(CODE_ALREADY_EXIST,error.summary());
		}
		Json::Value data_firebase;
		data_firebase["action"] = "FRIEND_REQUEST";
		data_firebase["id"] = source_user_id;
		string firebase_id = User::getFirebaseID(user_destination_id);
		FirebaseClient::sendNotifications(firebase_id,"Solicitud de amistad","El usuario " + source_user_id + " te ha enviado una solicitud de amistad.",data_firebase);
		return ResponseBuilder::createEmptyResponse(CODE_OK,"Solicitud para agregar a la red enviada");

	} else if (method == "DELETE"){

		ErrorMessage error = Friends::remove(source_user_id,user_destination_id);

		if (error){
			return ResponseBuilder::createErrorResponse(CODE_ALREADY_EXIST,"Usuario no es parte de la red");
		}

		return ResponseBuilder::createEmptyResponse(CODE_DELETE,"Eliminado de la red");
	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);

}

HTTPResponse* _friends(string source_user_id){

	Json::Value friends = Friends::listFriends(source_user_id);
	Json::Value online = Friends::listFriendsOnline(source_user_id);

	Json::Value metadata;
	metadata["version"] = "0.1";
	metadata["total"] = friends.size();
	metadata["count"] = friends.size();

	Json::Value general;
	general["metadata"] = metadata;
	general["friends"] = friends;
	general["online"] = online;

	return ResponseBuilder::createJsonResponse(CODE_OK,general);

}


HTTPResponse* _pendingFriends(string user_source_id){
	Json::Value friends = Friends::listPendingFriends(user_source_id);

	Json::Value metadata;
	metadata["version"] = "0.1";
	metadata["total"] = friends.size();
	metadata["count"] = friends.size();

	Json::Value general;
	general["metadata"] = metadata;
	general["friends"] = friends;

	return ResponseBuilder::createJsonResponse(CODE_OK,general);
}

