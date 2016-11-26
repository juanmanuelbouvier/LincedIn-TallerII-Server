#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_SEARCHHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_SEARCHHANDLER_H_

#include <services/Handlers/Handler.h>

class SearchHandler : public Handler {
public:
	SearchHandler(){};

	HTTPResponse* handle(HTTPRequest* request);

	virtual ~SearchHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_SEARCHHANDLER_H_ */
