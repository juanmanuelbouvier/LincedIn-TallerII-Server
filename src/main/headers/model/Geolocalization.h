#ifndef SRC_MAIN_SRC_MODEL_GEOLOCALIZATION_H_
#define SRC_MAIN_SRC_MODEL_GEOLOCALIZATION_H_

#include <services/DB/DB.h>
#include <model/User.h>
#include <list>
#include <extern/json.h>
#include <utils/GeoUtils.h>
using namespace std;

/**
 * Geolocalization is an object who manage the locations of users id.
 * Can search nearest users from location
 */
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
	/**
	 * Update location of user id
	 * @param Data. (format: { latitude, longitude, user_id }
	 * @return true if the update was successful
	 */
	static bool updateLocation( Json::Value data );

	/**
	 * Remove location from user id
	 * @param user id
	 * @return true if the delete was successful
	 */
	static bool remove(string user_id);

	/**
	 * Find nearest user from location
	 * @param data (Format: { latitude, longitude, range | optional })
	 * @return Json Array of nearest user with location, distances and timstamp of date into the range.
	 */
	static Json::Value findUsersByLocation( Json::Value data );

	/**
	 * Get user location
	 * @param user id
	 * @return Json Value with the location data (date of location, latitude, longitude). Empty if it does not have Geolocation
	 */
	static Json::Value getUserLocation( string user_id );

};

#endif /* SRC_MAIN_SRC_MODEL_GEOLOCALIZATION_H_ */
