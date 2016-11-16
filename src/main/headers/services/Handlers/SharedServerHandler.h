#ifndef SRC_MAIN_SERVICE_HANDLERS_SHAREDSERVERHANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_SHAREDSERVERHANDLER_H_

#include "Handler.h"

#include <vector>

class SharedServerHandler : public Handler {
public:
	SharedServerHandler(){};

	HTTPResponse* handle(HTTPRequest* http_request);

	vector<string> getKnowURLs();

	virtual ~SharedServerHandler(){};
};

#endif /* SRC_MAIN_SERVICE_HANDLERS_SHAREDSERVERHANDLER_H_ */
