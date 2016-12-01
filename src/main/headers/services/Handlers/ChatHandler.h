#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_

#include "Handler.h"

class ChatHandler : public Handler {
private:

public:
	ChatHandler(){};

	/**
	 * With Chat handler can:
	 * 	- Create or delete chat.
	 *  - Send Message
	 *  - Get Chat or chats of user
	 *  - Get friends who is online
	 */
	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~ChatHandler(){};

};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_ */
