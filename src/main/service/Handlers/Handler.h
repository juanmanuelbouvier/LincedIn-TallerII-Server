/*
 * AbstractHandler.h
 *
 *  Created on: 5 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_

#include "../MongooseServer/HTTP/HTTPRequest.h"
#include <iostream>
using namespace std;

class Handler {

public:
	virtual string handle(HTTPRequest* http_request) = 0;
	virtual ~Handler(){};
};


#endif /* SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_ */
