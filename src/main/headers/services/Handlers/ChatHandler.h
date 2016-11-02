#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_

#include "Handler.h"

class ChatHandler : public Handler {
public:

	ChatHandler(){};
	HTTPResponse* handle(HTTPRequest* http_request);
	virtual ~ChatHandler(){};

};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_CHATHANDLER_H_ */
