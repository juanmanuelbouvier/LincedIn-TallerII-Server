#ifndef SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_
#define SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_


#include <services/Handlers/Handler.h>
#include "Message/HTTPRequest.h"
#include "Message/HTTPResponse.h"

#include <map>


using namespace std;

class HTTPRequestHandler {

private:
	map<string,Handler*> HTTPEndPointsHandlers;

public:
	HTTPRequestHandler();

	HTTPResponse* handle(HTTPRequest* http_request);

	bool isHandledRequest(HTTPRequest* http_request);

	virtual ~HTTPRequestHandler();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_ */
