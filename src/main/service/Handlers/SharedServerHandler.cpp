#include "SharedServerHandler.h"
#include "../Logger/Logger.h"

SharedServerHandler::SharedServerHandler() {
}

string SharedServerHandler::handle(HTTPRequest* http_request){
	Json::Value event;
	
	Json::Value skills(Json::arrayValue);
	event["skills"] = skills;

	Json::Value skill1;
	skill1["name"] = "c";
	skill1["category"] = "software";
	skill1["description"] = "Lenguaje de programación C";

	Json::Value skill2;
	skill2["name"] = "python";
	skill2["category"] = "software";
	skill2["description"] = "Lenguaje de programación python";

	event["skills"].append(skill1);
	event["skills"].append(skill2);

	Json::Value metadata;
	//version del servr
	metadata["version"] = "0.1";
	metadata["count"] = 2;
	event["metadata"] = metadata;

	Json::FastWriter writer;
	writer.omitEndingLineFeed();
	string toReturn = writer.write(event);

	string body = "\r\nContent-type:application/json\r\n\r\n" + toReturn + "\r\n";
	return body.c_str();
}

SharedServerHandler::~SharedServerHandler(){

}
