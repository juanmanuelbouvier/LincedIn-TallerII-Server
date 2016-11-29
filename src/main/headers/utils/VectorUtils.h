#ifndef SRC_MAIN_UTILS_VECTORUTILS_H_
#define SRC_MAIN_UTILS_VECTORUTILS_H_


#include <vector>
#include <list>
#include <sstream>


using namespace std;

class VectorUtils {
public:
	//! Join a vector of strings with a separator.
	//!
	//! @param theVector The vector who be splitet
	//! @param Separator default value is a space " ".
	//! @return String who contain the elements of the vector separated by separator.
	static string joinVector(vector<string> theVector, string separator = " ");

};

#endif /* SRC_MAIN_UTILS_VECTORUTILS_H_ */
