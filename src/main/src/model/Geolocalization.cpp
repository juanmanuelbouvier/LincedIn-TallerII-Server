#include <model/Geolocalization.h>
#include <utils/DateUtils.h>
#include <services/DB/DBManager.h>
#include <vector>
#include <utils/StringUtils.h>
#include <model/User.h>

#define GEO_DB "Geolocalization"
#define USER_GEO_DB "User_Geolocalization"

#define PRECISION_KEY 2
#define MAX_RANGE 100
#define SEPARATOR "#"

#define DEFAULT_DISTANCE_ERROR 1;

DB* Geolocalization::getDB() {
	return DBManager::getDB(GEO_DB);
}

DB* Geolocalization::getLastGeoDB() {
	return DBManager::getDB(USER_GEO_DB);
}

bool Geolocalization::remove(string user_id) {
	string key = getLastGeoDB()->get(user_id);
	if (!key.empty() && getDB()->exist(key)){
		Json::Value dbData = getDB()->getJSON(key);
		dbData.removeMember(user_id);
		return (getDB()->storeJSON(key,dbData) && getLastGeoDB()->Delete(user_id));
	}
	return true;
}


bool Geolocalization::updateDBs(string key, Json::Value data ) {
	string user_id = data["user_id"].asString();
	bool noOldInformation = true;
	if (getLastGeoDB()->exist(user_id) && getLastGeoDB()->get(user_id) != key) {
		noOldInformation = remove(user_id);
	}

	Json::Value dbData;
	if ( getDB()->exist(key) ) {
		dbData = getDB()->getJSON(key);
	}
	dbData[user_id] = data[GEO_DB];
	return ( noOldInformation && getDB()->storeJSON(key,dbData) && getLastGeoDB()->store(user_id,key) );
}

bool Geolocalization::validData( Json::Value data ) {
	return ( data.isMember("latitude") && data["latitude"].isConvertibleTo(Json::stringValue) &&
			data.isMember("longitude") && data["longitude"].isConvertibleTo(Json::stringValue)
			);
}

string Geolocalization::generateKey( Json::Value data ) {
	double latitude  = stod(data["latitude"].asString());
	double longitude = stod(data["longitude"].asString());
	string latKey = to_string( GeoUtils::roundNumber((double)latitude, PRECISION_KEY) );
	string lonKey = to_string( GeoUtils::roundNumber((double)longitude, PRECISION_KEY) );
	return latKey + SEPARATOR + lonKey;

}

string Geolocalization::generateKey( Location location ) {
	Json::Value data;
	data["latitude"] = location.latitude;
	data["longitude"] = location.longitude;
	return generateKey(data);
}

bool Geolocalization::updateLocation( Json::Value data ) {
	if ( !validData(data) ) {
		return false;
	}

	if ( !data.isMember("user_id") || !data["user_id"].isString() || !User::exist(data["user_id"].asString()) ) {
		return false;
	}

	Json::Value dataToGeoDB;
	dataToGeoDB["timestamp"] = DateUtils::timestamp();
	Json::Value geolocalization;
	geolocalization["latitude"] = data["latitude"];
	geolocalization["longitude"] = data["longitude"];
	dataToGeoDB["geolocalization"] = geolocalization;

	Json::Value dataToStore;
	dataToStore["user_id"] = data["user_id"];
	dataToStore[GEO_DB] = dataToGeoDB;

	Location location = { stod( data["latitude"].asString() ), stod( data["longitude"].asString() ) };
	if (!GeoUtils::isValid(location)) {
		return false;
	}
	string key = generateKey(data);

	return updateDBs( key, dataToStore );

}

Json::Value Geolocalization::collectLocations( Location fromLocation, list<Location> locations, double range ) {
	Json::Value found;
	for (Location & location : locations) {
		string keyForLocation = generateKey(location);
		if ( getDB()->exist(keyForLocation) ) {
			Json::Value data = getDB()->getJSON(keyForLocation);
			Json::Value::Members users_id_members = data.getMemberNames();
			for ( string& user_id : users_id_members ) {
				Json::Value user_data = data[user_id];
				double latitude = stod(user_data["geolocalization"]["latitude"].asString());
				double longitude = stod(user_data["geolocalization"]["longitude"].asString());
				Location user_location = { latitude, longitude };
				double distance = GeoUtils::distance(fromLocation, user_location);
				if ( distance <= range ) {
					user_data["distance"] = distance;
					found[user_id] = user_data;
				}
			}
		}
	}
	return found;
}

Json::Value Geolocalization::findUsersByLocation( Json::Value data ) {
	Json::Value dataFound;
	if ( validData(data) ) {
		double latitude = stod( data["latitude"].asString() );
		double longitude = stod( data["longitude"].asString() );
		Location location = { latitude, longitude };
		if ( GeoUtils::isValid(location) ) {
			double range = ( data.isMember("range") && data["range"].isConvertibleTo(Json::stringValue) ) ? stod( data["range"].asString() ) : DEFAULT_DISTANCE_ERROR;
			if (range > MAX_RANGE || range < 0) {
				dataFound["error"] = "Are you seriously telling me to look in a range of " + to_string(range) + " km?. Max is " + to_string(MAX_RANGE) + "km and Min is 0 km.";
				return dataFound;
			}
			list<Location> neighbours = GeoUtils::getNeighbours(location,range,PRECISION_KEY);
			neighbours.push_back( location );
			dataFound = collectLocations( location, neighbours, range );
		}
	}
	return dataFound;
}


Json::Value Geolocalization::getUserLocation( string user_id ) {
	Json::Value found;
	string key = getLastGeoDB()->get(user_id);
	if (!key.empty()) {
		if (getDB()->exist(key)) {
			Json::Value geoData = getDB()->getJSON(key);
			found = geoData[user_id];
		}
	}
	return found;
}

