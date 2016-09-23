/*
 * HTTPRequestHandler.h
 *
 *  Created on: 7 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_
#define SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_

#include "../../Handlers/HelloWorldJsonHandler.h"
#include "../../Handlers/DefaultHandler.h"
#include "../../Logger/Logger.h"

#include "HTTPRequest.h"

#include <map>

using namespace std;

class HTTPRequestHandler {

private:
	map<string,Handler*> HTTPEndPointsHandlers;

public:
	HTTPRequestHandler();

	string handle(HTTPRequest* http_request);

	bool isHandledRequest(HTTPRequest* http_request);

	virtual ~HTTPRequestHandler();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_ */
