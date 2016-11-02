#include <services/Handlers/ChatHandler.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>

Json::Value createChat(string id, string name, string message, int time) {
	Json::Value m;
	m["user_id"] = id;
	m["user_name"] = name;
	m["message"] = message;
	m["timestamp"] = time;

	return m;
}

HTTPResponse* ChatHandler::handle(HTTPRequest* http_request) {

	string chat = "";
	int code = 200;

	map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/chat/:user_id");
	string user_destination = path["user_id"];

	if (http_request->getMethod() == "GET") {

		Json::Value messages(Json::arrayValue);

		messages.append( createChat("user1","tú","hola",1476852631) );
		messages.append( createChat("user1","tú","como andas?",1476852661) );
		messages.append( createChat(user_destination,user_destination,"Hey... bien y vos?",1476852681) );
		messages.append( createChat("user1","tú","Bien. Que hacias?",1476854631) );
		messages.append( createChat(user_destination,user_destination,"nada al pedo, vos",1476855631) );
		messages.append( createChat(user_destination,user_destination,"respondeeeeee",1476856631) );
		messages.append( createChat(user_destination,user_destination,"chau :(",1476857631) );

		Json::Value metadata;
		metadata["version"] = 0.1;
		metadata["total"] = 5;
		metadata["count"] = 5;

		Json::Value general;
		general["metadata"] = metadata;
		general["messages"] = messages;

		Json::FastWriter writer;
		writer.omitEndingLineFeed();
		chat = writer.write(general);
	}

	ResponseBuilder* response = new ResponseBuilder();
	response = (ResponseBuilder*)response->appendHeader("Content-type","application/json")->setBody(chat);
	response = response->setCode(code);

	return response->build();
}

