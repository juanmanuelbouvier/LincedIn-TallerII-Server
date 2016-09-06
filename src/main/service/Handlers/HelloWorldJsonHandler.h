/*
 * HelloWorldJsonHandler.h
 *
 *  Created on: 5 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_

#include "Handler.h"
#include "../Json/json/json.h"

using namespace std;

class HelloWorldJsonHandler : public Handler {
public:
	HelloWorldJsonHandler();

	char* handle();

	virtual ~HelloWorldJsonHandler();
};


#endif /* SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_ */
