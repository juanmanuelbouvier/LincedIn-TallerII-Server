#ifndef SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_

#include "../HTTP/Message/HTTPRequest.h"
#include "../HTTP/Message/HTTPResponse.h"

/**
 * Abstract class Handler is a HTTP Handler who has asigned one or more endpoints and can handle and http request.
 */
class Handler {

public:
	/**
	 * Handle an HTTP Request
	 * @note This method must be implemented in any handler that is created and inherits to perform an action on the model
	 * @param A request who arrive from HTTP Handlers.
	 * @return A response after an action.
	 */
	virtual HTTPResponse* handle(HTTPRequest* http_request) = 0;
	virtual ~Handler(){};
};


#endif /* SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_ */
