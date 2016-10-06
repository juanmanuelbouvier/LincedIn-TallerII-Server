#ifndef SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_

#include "Handler.h"
#include "../Json/json/json.h"

using namespace std;

class HelloWorldJsonHandler : public Handler {
public:
	HelloWorldJsonHandler();

	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~HelloWorldJsonHandler();
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_HELLOWORLDJSONHANDLER_H_ */
