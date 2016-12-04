#include <services/Handlers/SharedServerHandler.h>
#include <services/SharedServerAPI/SharedServerAPI.h>

#include <services/Logger/Logger.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <extern/json.h>
#include <string>

#define PREFIX "/shared"

vector<string> SharedServerHandler::getKnowURLs(){
	vector<string> endPoints = {
			"/job_positions/categories/:category",
			"/job_positions",
			"/skills",
			"/skills/categories/:category/:name",
			"/categories"
	};
	for (int i = 0; i < endPoints.size(); i++ ) {
		endPoints[i] = string(PREFIX) + endPoints[i];
	}
	return endPoints;
}

HTTPResponse* SharedServerHandler::handle(HTTPRequest* http_request){
	string uri = http_request->getURI();
	uri = uri.substr( string(PREFIX).size(),uri.size() );
	SharedServerAPI shared;
	HTTPResponse* res;
	if (uri == "/skills") {
		Json::Value data;
		data["skills"] = shared.getSkills();
		res = ResponseBuilder::createJsonResponse(200,data);
	} else if ( uri == "/job_positions" ) {
		Json::Value data;
		data["job_positions"] = shared.getJobPositions();
		res = ResponseBuilder::createJsonResponse(200,data);
	} else {
		Log("SharedServerHandler: call shared with uri: " + uri,INFO);
		res = shared.doGet(uri);
	}
	return res;
}
