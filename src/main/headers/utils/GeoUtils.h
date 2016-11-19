#ifndef SRC_MAIN_SRC_UTILS_GEOUTILS_H_
#define SRC_MAIN_SRC_UTILS_GEOUTILS_H_

#include <list>

using namespace std;

struct Location {
	double latitude;
	double longitude;
};

struct Range {
	double latitude;
	double longitude;
};

class GeoUtils {
private:
	static constexpr double EARTH_RADIUS_KM = 6371;
	static constexpr double UNIT_VARIATION_LON_KM = 77.5207167632;
	static constexpr double UNIT_VARIATION_LAT_KM = 111.194926645;
	static double degToRad( double input );
	static Range getRangeVariation( double range );

public:
	static double distance(Location from, Location to);
	static double roundNumber( double number, int decimals );
	static list<Location> getNeighbours(Location from, double range, int decimals);
	static bool isValid( Location location );
};

#endif /* SRC_MAIN_SRC_UTILS_GEOUTILS_H_ */
