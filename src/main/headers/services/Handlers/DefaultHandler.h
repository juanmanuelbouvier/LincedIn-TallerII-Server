#ifndef SRC_MAIN_SERVICE_HANDLERS_DEFAULTHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_DEFAULTHANDLER_H_

#include "Handler.h"

class DefaultHandler : public Handler {
public:
	DefaultHandler(){};

	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~DefaultHandler(){};
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_DEFAULTHANDLER_H_ */
