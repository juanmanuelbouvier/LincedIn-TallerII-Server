#include <services/Handlers/SharedServerHandler.h>
#include <services/SharedServerAPI/SharedServerAPI.h>

#include <services/Logger/Logger.h>
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
	Log("SharedServerHandler: call shared with uri: " + uri,INFO);
	SharedServerAPI shared;
	return shared.doGet(uri);
}
