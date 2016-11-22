#ifndef SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_
#define SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_


#include <services/Handlers/Handler.h>
#include "Message/HTTPRequest.h"
#include "Message/HTTPResponse.h"

#include <map>
#include <vector>


using namespace std;

class HTTPRequestHandler {

private:
	map<string,Handler*> HTTPEndPointsHandlers;
	vector<string> workingPaths;

	string matchPath( string uri );
	void registerPath( string path );
	void accessLog(HTTPRequest* http_request);

public:
	HTTPRequestHandler();

	HTTPResponse* handle(HTTPRequest* http_request);

	bool isHandledRequest(HTTPRequest* http_request);
	bool addHandler(string uri_path, Handler* handler);

	virtual ~HTTPRequestHandler();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_ */
