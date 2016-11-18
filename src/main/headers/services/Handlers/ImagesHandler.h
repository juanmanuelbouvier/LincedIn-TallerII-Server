#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_IMAGESHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_IMAGESHANDLER_H_

#include "Handler.h"

using namespace std;

class ImagesHandler : public Handler{
public:
	ImagesHandler(){};
	HTTPResponse* handle(HTTPRequest* http_request);
	virtual ~ImagesHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_IMAGESHANDLER_H_ */
