#ifndef SRC_MAIN_UTILS_STRINGUTILS_H_
#define SRC_MAIN_UTILS_STRINGUTILS_H_

#include <string>
#include <vector>
#include <string.h>

using namespace std;

class StringUtils {
public:
	static vector<string> splitString(string the_string, string delimiter = " ");
};

#endif /* SRC_MAIN_UTILS_STRINGUTILS_H_ */
