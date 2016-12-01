#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_SEARCHHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_SEARCHHANDLER_H_

#include <services/Handlers/Handler.h>

class SearchHandler : public Handler {
public:
	SearchHandler(){};

	/**
	 * Search User Handler can:
	 *  - Filter user with match a query (1)
	 *  - Filter user by skill (1)
	 *  - Filter user by geolocalization
	 *  - Filter most recommended users
	 * @note `(1)` Depends on Elastic search
	 */
	HTTPResponse* handle(HTTPRequest* request);

	virtual ~SearchHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_SEARCHHANDLER_H_ */
