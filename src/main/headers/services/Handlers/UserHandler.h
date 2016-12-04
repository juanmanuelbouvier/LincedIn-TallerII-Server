#ifndef SRC_MAIN_SERVICE_HANDLERS_USERHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_USERHANDLER_H_

#include "Handler.h"
#include <extern/json.h>

class UserHandler : public Handler {
public:
	UserHandler(){};

	/**
	 * User handler can:
	 *  - Get user data.
	 *  - Edit user data.
	 *  - Create user.
	 *  - Remove user.
	 */
	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~UserHandler(){};
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_USERHANDLER_H_ */
