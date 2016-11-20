#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_RECOMMENDATIONHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_RECOMMENDATIONHANDLER_H_

#include <services/Handlers/Handler.h>

class RecommendationHandler : public Handler {
public:
	RecommendationHandler(){};
	HTTPResponse* handle(HTTPRequest* request);
	virtual ~RecommendationHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_RECOMMENDATIONHANDLER_H_ */
