#ifndef SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_

#include "Handler.h"

class HelloWorldJsonHandler : public Handler {
public:
	HelloWorldJsonHandler(){};

	/**
	 * It is a Dummy Handler to Debug and test
	 */
	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~HelloWorldJsonHandler(){};
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_ */
