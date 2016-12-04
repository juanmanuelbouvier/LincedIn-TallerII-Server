#ifndef SRC_MAIN_SRC_UTILS_GEOUTILS_H_
#define SRC_MAIN_SRC_UTILS_GEOUTILS_H_

#include <list>

using namespace std;

struct Location {
	double latitude;
	double longitude;
};

struct Range {
	double offset_latitude;
	double offset_longitude;
};

class GeoUtils {
private:
	static constexpr double EARTH_RADIUS_KM = 6371;
	static constexpr double UNIT_VARIATION_LON_KM = 77.5207167632;
	static constexpr double UNIT_VARIATION_LAT_KM = 111.194926645;

	/**
	 * Convert deg to Radias
	 * @param deg input.
	 * @return Rad value of input.
	 */
	static double degToRad( double input );

	/**
	 * Get Range offset variation of latitude and longitude.
	 * @note This depends of units variations of components.
	 * @param Desidered range.
	 * @return Range who contains offsets of longitude and latitude.
	 */
	static Range getRangeVariation( double range );

public:
	/**
	 * Get the distance in Kilometers between two locations
	 * @param Location one
	 * @param Location two
	 * @return Distance in kilometers
	 */
	static double distance(Location from, Location to);

	/**
	 * Round number with especified decimals
	 * @param Number to be rounded
	 * @return Rounded number with `decimals` decimals
	 * ej. roundNumber(2.876542,3) ==> 2.877S
	 */
	static double roundNumber( double number, int decimals );

	/**
	 * Get locations neighbours of specified location who be rounded with decimals and desidered range
	 * @param Number to be rounded
	 * @return Rounded number with `decimals` decimals
	 * ej. roundNumber(2.876542,3) ==> 2.877S
	 */
	static list<Location> getNeighbours(Location from, double range, int decimals);

	/**
	 * Check if Location has valid values respect standard coordinates.
	 * @param Location
	 * @return True if is valid
	 */
	static bool isValid( Location location );
};

#endif /* SRC_MAIN_SRC_UTILS_GEOUTILS_H_ */
