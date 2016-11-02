#include <services/Handlers/ChatHandler.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>

Json::Value _createChat(string id, string name, string message, int time) {
	Json::Value m;
	m["user_id"] = id;
	m["user_name"] = name;
	m["message"] = message;
	m["timestamp"] = time;

	return m;
}

Json::Value _createOnlineUser(string id, string name) {

	Json::Value user;
	user["user_id"] = id;
	user["user_name"] = name;

	return user;
}

Json::Value _createSummaryChat(string id, string name, string last_message, int time) {
	Json::Value m;
	m["user_id"] = id;
	m["user_name"] = name;
	m["last_message"] = last_message;
	m["timestamp"] = time;

	return m;
}

HTTPResponse* _chatWithUser(string method,string user_id);
HTTPResponse* _online(string method);
HTTPResponse* _chats();

HTTPResponse* ChatHandler::handle(HTTPRequest* http_request) {


	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat")){
		return _chats();

	} else if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat/online")) {
		return _online(http_request->getMethod());
	} else {

		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/chat/:user_id");
		return _chatWithUser(http_request->getMethod(),path["user_id"]);

	}
}

HTTPResponse* _chatWithUser(string method,string user_id){
	if (method == "GET") {
		string chat = "";
		string user_destination = user_id;

		Json::Value messages(Json::arrayValue);

		messages.append( _createChat("Un usuario","tú","hola",1476852631) );
		messages.append( _createChat("Un usuario","tú","como andas?",1476852661) );
		messages.append( _createChat(user_destination,user_destination,"Hey... bien y vos?",1476852681) );
		messages.append( _createChat("Un usuario","tú","Bien. Que hacias?",1476854631) );
		messages.append( _createChat(user_destination,user_destination,"nada al pedo, vos",1476855631) );
		messages.append( _createChat(user_destination,user_destination,"respondeeeeee",1476856631) );
		messages.append( _createChat(user_destination,user_destination,"chau :(",1476857631) );

		Json::Value metadata;
		metadata["version"] = "0.1";
		metadata["total"] = 5;
		metadata["count"] = 5;

		Json::Value general;
		general["metadata"] = metadata;
		general["messages"] = messages;

		Json::FastWriter writer;
		writer.omitEndingLineFeed();
		chat = writer.write(general);

		return ResponseBuilder::createJsonResponse(200,chat);
	}

	return ResponseBuilder::createErrorResponse(400,"BAD REQUEST");
}

HTTPResponse* _online(string method){

	if (method == "GET") {

		string user = "Tu usuario";

		Json::Value online(Json::arrayValue);

		online.append( _createOnlineUser("cfontela","Carlos Fontela") );
		online.append( _createOnlineUser("tbert","Tomas Bert") );
		online.append( _createOnlineUser("fetchachu","Facundo Etchanchú") );
		online.append( _createOnlineUser("jbouvier","Juanma Bouvier") );


		Json::Value metadata;
		metadata["version"] = "0.1";
		metadata["total"] = 4;
		metadata["count"] = 4;

		Json::Value general;
		general["metadata"] = metadata;
		general["online"] = online;

		Json::FastWriter writer;
		writer.omitEndingLineFeed();

		return ResponseBuilder::createJsonResponse(200,writer.write(general));
	}
	return ResponseBuilder::createErrorResponse(400,"BAD REQUEST");
}


HTTPResponse* _chats(){
	string user = "Tu usuario";

	Json::Value chats(Json::arrayValue);

	chats.append( _createSummaryChat("cfontela","Carlos Fontela","chau che, nos vemos! CF.",1476852631) );
	chats.append( _createSummaryChat("fetchanchu","Facundo Etchanchú","Pagame lo que me debés!",1476854631) );
	chats.append( _createSummaryChat("oiogha","Octavio Iogha","Dale, en 20 lo subo.",1476855631));

	Json::Value metadata;
	metadata["version"] = "0.1";
	metadata["total"] = 3;
	metadata["count"] = 3;

	Json::Value general;
	general["metadata"] = metadata;
	general["chats"] = chats;

	Json::FastWriter writer;
	writer.omitEndingLineFeed();

	return ResponseBuilder::createJsonResponse(200,writer.write(general));

}

