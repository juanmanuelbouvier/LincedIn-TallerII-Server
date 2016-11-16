#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_

#include "Handler.h"

class ChatHandler : public Handler {
private:
	//HTTPResponse* getChatsFrom(User user);
	//HTTPResponse* getOnlineFriendsFrom(User user);
	//HTTPResponse* handleChat(User user, string chat_id);

public:
	ChatHandler(){};
	HTTPResponse* handle(HTTPRequest* http_request);
	virtual ~ChatHandler(){};

};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_ */
