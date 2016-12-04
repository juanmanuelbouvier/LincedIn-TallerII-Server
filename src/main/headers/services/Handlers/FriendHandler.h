#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_FRIENDHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_FRIENDHANDLER_H_

#include "Handler.h"

class FriendHandler : public Handler {
public:

	FriendHandler(){};

	/**
	 * Friend Handler can:
	 *	- View pending friend requests
	 *	- Send, Accept or decline friend requests
	 */
	HTTPResponse* handle(HTTPRequest* http_request);
	virtual ~FriendHandler(){};

};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_FRIENDHANDLER_H_ */
