#include <utils/GeoUtils.h>
#include <math.h>
#include <stdio.h>

double GeoUtils::degToRad(double deg){
	return (deg * M_PI / 180);
}

double GeoUtils::roundNumber(double number, int decimals) {
	if (decimals < 0) return number;
	return round( number * pow(10, decimals) ) / pow(10, decimals);
}

bool GeoUtils::isValid(Location location) {
	if ( location.latitude <= 90.0 && location.latitude >= -90.0 ) {
		if ( location.longitude <= 180 && location.longitude >= -180 ) {
			return true;
		}
	}
	return false;
}

Range GeoUtils::getRangeVariation( double rangeDistance ) {
	double latitudeRange  = (rangeDistance != 0) ? rangeDistance/UNIT_VARIATION_LAT_KM : 0;
	double longitudeRange = (rangeDistance != 0) ? rangeDistance/UNIT_VARIATION_LON_KM : 0;
	Range range = { latitudeRange, longitudeRange };
	return range;
}

double GeoUtils::distance(Location from, Location to) {
	double lat1r = degToRad(from.latitude);
	double lon1r = degToRad(from.longitude);
	double lat2r = degToRad(to.latitude);
	double lon2r = degToRad(to.longitude);
	double dU = sin( (lat2r - lat1r)/2 );
	double dV = sin( (lon2r - lon1r)/2 );
	return 2.0 * EARTH_RADIUS_KM * asin(sqrt(dU * dU + cos(lat1r) * cos(lat2r) * dV * dV));
}

list<Location> GeoUtils::getNeighbours(Location from, double rangeLocation, int decimals) {
	list<Location> neighbours;

	Range range = getRangeVariation(rangeLocation);

	double putComma = pow(10,-decimals);
	double delComma	= pow(10, decimals);

	int lat = roundNumber(from.latitude, decimals)*delComma;
	int lon = roundNumber(from.longitude, decimals)*delComma;
	int rangeLat = roundNumber(range.offset_latitude, decimals)*delComma;
	int rangeLon = roundNumber(range.offset_longitude, decimals)*delComma;

	rangeLat = (rangeLat == 0) ? 1 : rangeLat;
	rangeLon = (rangeLon == 0) ? 1 : rangeLon;

	for ( int nLat = lat - rangeLat; nLat <= lat + rangeLat; nLat = nLat + 1 ) {
		for ( int nLon = lon - rangeLon; nLon <= lon + rangeLon; nLon = nLon + 1 ) {
			if ( nLat == lat && nLon == lon )
				continue;
			Location neighbour = { nLat*putComma, nLon*putComma };
			if (isValid(neighbour)) {
				neighbours.push_back(neighbour);
			}
		}
	}
	return neighbours;
}
