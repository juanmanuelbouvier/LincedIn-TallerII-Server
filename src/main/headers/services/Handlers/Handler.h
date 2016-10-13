#ifndef SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_

#include "../HTTP/Message/HTTPRequest.h"
#include "../HTTP/Message/HTTPResponse.h"


class Handler {

public:
	virtual HTTPResponse* handle(HTTPRequest* http_request) = 0;
	virtual ~Handler(){};
};


#endif /* SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_ */
