/*
 * AbstractHandler.h
 *
 *  Created on: 5 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_

#include "../HTTP/Message/HTTPRequest.h"
#include "../HTTP/Message/HTTPResponse.h"
#include "../HTTP/Message/HTTPMessageBuilder.h"
#include "../SharedServerAPI/SharedServerAPI.h"
#include <iostream>
using namespace std;

class Handler {

public:
	virtual HTTPResponse* handle(HTTPRequest* http_request) = 0;
	virtual ~Handler(){};
};


#endif /* SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_ */
