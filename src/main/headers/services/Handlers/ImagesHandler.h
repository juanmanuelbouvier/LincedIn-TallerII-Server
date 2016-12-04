#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_IMAGESHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_IMAGESHANDLER_H_

#include "Handler.h"

using namespace std;

class ImagesHandler : public Handler{
public:
	ImagesHandler(){};
	/**
	 * Image Handler can get image wha was stored in platform
	 */
	HTTPResponse* handle(HTTPRequest* http_request);
	virtual ~ImagesHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_IMAGESHANDLER_H_ */
