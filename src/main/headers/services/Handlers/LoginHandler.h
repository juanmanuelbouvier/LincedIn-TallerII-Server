#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_LOGINHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_LOGINHANDLER_H_

#include <services/Handlers/Handler.h>

class LoginHandler : public Handler {
public:
	LoginHandler(){};

	HTTPResponse* handle(HTTPRequest* request);

	virtual ~LoginHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_LOGINHANDLER_H_ */
