#include <services/Handlers/SharedServerHandler.h>
#include <services/SharedServerAPI/SharedServerAPI.h>

#include <services/Logger/Logger.h>
#include <string>

#define PREFIX "/shared"

vector<string> SharedServerHandler::getKnowURLs(){
	SharedServerAPI shared;
	vector<string> gets = shared.getsURL();
	for (int i = 0; i < gets.size(); i++ ) {
		gets[i] = string(PREFIX) + gets[i];
	}
	return gets;
}

HTTPResponse* SharedServerHandler::handle(HTTPRequest* http_request){
	string uri = http_request->getURI();
	uri = uri.substr( string(PREFIX).size(),uri.size() );
	Log("SharedServerHandler: call shared with uri: " + uri,INFO);
	SharedServerAPI shared;
	return shared.doGet(uri);
}
