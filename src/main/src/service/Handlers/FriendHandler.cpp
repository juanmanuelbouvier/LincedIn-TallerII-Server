#include <services/Handlers/FriendHandler.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <extern/json.h>

using namespace std;

HTTPResponse* _actionUser(string method,string user_destination_id);
HTTPResponse* _friends();

HTTPResponse* FriendHandler::handle(HTTPRequest* http_request) {

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/friends/:destination_user_id")){

		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/friends/:destination_user_id");

		return _actionUser(http_request->getMethod(),path["destination_user_id"]);

	} else {

		return _friends();

	}

}


HTTPResponse* _actionUser(string method,string user_destination_id){

	if (method == "POST"){

		//agregar amigo

	} else if (method == "DELETE"){

		//eliminar amigo

	}

	return ResponseBuilder::createErrorResponse(400,"BAD REQUEST");

}

Json::Value _createFriend(string user_id, string name) {

	Json::Value fr;
	fr["user_id"] = user_id;
	fr["user_name"] = name;

	return fr;
}

HTTPResponse* _friends(){

	Json::Value friends(Json::arrayValue);

	friends.append( _createFriend("ssantisi","Sebastían Santisi"));
	friends.append( _createFriend("fetchanchu","Facundo Etchanchú"));
	friends.append( _createFriend("tbert","Tomás Bert"));
	friends.append( _createFriend("netchanchu","Norberto Etchanchú"));
	friends.append( _createFriend("cfaccineti","Carlos Federico Faccineti"));

	Json::Value metadata;
	metadata["version"] = "0.1";
	metadata["total"] = 5;
	metadata["count"] = 5;

	Json::Value general;
	general["metadata"] = metadata;
	general["friends"] = friends;

	Json::FastWriter writer;
	writer.omitEndingLineFeed();

	return ResponseBuilder::createJsonResponse(200,writer.write(general));

}




