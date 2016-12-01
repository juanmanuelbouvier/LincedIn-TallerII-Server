#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_LOGINHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_LOGINHANDLER_H_

#include <services/Handlers/Handler.h>

class LoginHandler : public Handler {
public:
	LoginHandler(){};

	/**
	 *  LoginHandler Can
	 *   - Generate a session (Token) for user with password and email/userid
	 *   - Generate a session for user who was logged with Facebook app
	 *   - Create a user (if not exist) from Facebook User
	 */
	HTTPResponse* handle(HTTPRequest* request);

	virtual ~LoginHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_LOGINHANDLER_H_ */
