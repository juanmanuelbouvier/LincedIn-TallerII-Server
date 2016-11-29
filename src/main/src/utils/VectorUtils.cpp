#include <utils/VectorUtils.h>
#include <iostream>


string VectorUtils::joinVector(vector<string> theVector, string separator) {
	stringstream ss;
	for(size_t i = 0; i < theVector.size(); ++i) {
		string putSeparator = ( i + 1 == theVector.size() ) ? "" : separator;
		ss << theVector[i] + putSeparator;
	}
	return ss.str();
}

