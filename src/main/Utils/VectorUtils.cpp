#include "VectorUtils.h"

//! Join a vector of strings with a separator.
//!
//! @param theVector The vector who be splitet
//! @param Separator default value is a space " ".
//! @return String who contain the elements of the vector separated by separator.
string joinVector(vector<string> theVector, string separator) {
	stringstream ss;
	for(size_t i = 0; i < theVector.size(); ++i) {
		string putSeparator = ( i + 1 == theVector.size() ) ? "" : separator;
		ss << theVector[i] + putSeparator;
	}
	return ss.str();
}
