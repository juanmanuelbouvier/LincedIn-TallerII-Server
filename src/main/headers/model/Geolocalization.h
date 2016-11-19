#ifndef SRC_MAIN_SRC_MODEL_GEOLOCALIZATION_H_
#define SRC_MAIN_SRC_MODEL_GEOLOCALIZATION_H_

#include <services/DB/DB.h>
#include <model/User.h>
#include <list>
#include <extern/json.h>
#include <utils/GeoUtils.h>
using namespace std;

class Geolocalization {
private:
	static DB* getDB();
	static DB* getLastGeoDB();
	static bool validData(Json::Value data);
	static bool updateDBs( string key, Json::Value data );

	static string generateKey( Json::Value data );
	static string generateKey( Location location );

	static Json::Value collectLocations( Location fromLocation,list<Location> locations, double range );

public:
	static bool updateLocation( Json::Value data );
	static bool remove(string user_id);
	static Json::Value findUsersByLocation( Json::Value location );
	static Json::Value getUserLocation( string user_id );

};

#endif /* SRC_MAIN_SRC_MODEL_GEOLOCALIZATION_H_ */
