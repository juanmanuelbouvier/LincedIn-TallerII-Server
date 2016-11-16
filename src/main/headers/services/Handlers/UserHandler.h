#ifndef SRC_MAIN_SERVICE_HANDLERS_USERHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_USERHANDLER_H_

#include "Handler.h"
#include <extern/json.h>

class UserHandler : public Handler {
private:
	Json::Value _createUser(string user_id);
public:
	UserHandler(){};

	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~UserHandler(){};
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_USERHANDLER_H_ */
