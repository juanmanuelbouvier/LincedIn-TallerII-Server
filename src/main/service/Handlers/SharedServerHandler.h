#ifndef SRC_MAIN_SERVICE_HANDLERS_SHAREDSERVERHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_SHAREDSERVERHANDLER_H_

#include "Handler.h"
#include "../Json/json/json.h"

using namespace std;

class SharedServerHandler : public Handler {
public:
	SharedServerHandler();

	HTTPResponse* handle(HTTPRequest* http_request);

	virtual ~SharedServerHandler();
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_SHAREDSERVERHANDLER_H_ */
