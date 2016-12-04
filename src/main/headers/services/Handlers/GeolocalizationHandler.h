#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_GEOLOCALIZATIONHANDLER_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_GEOLOCALIZATIONHANDLER_H_

#include <services/Handlers/Handler.h>

class GeolocalizationHandler : public Handler {
public:
	GeolocalizationHandler(){};

	/**
	 * Geolocalization Handler can.
	 * 	- Get neares friends.
	 * 	- Post or get a geolocation of user.
	 */
	HTTPResponse* handle(HTTPRequest* request);

	virtual ~GeolocalizationHandler(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_GEOLOCALIZATIONHANDLER_H_ */
