#ifndef SRC_MAIN_UTILS_STRINGUTILS_H_
#define SRC_MAIN_UTILS_STRINGUTILS_H_

#include <string>
#include <vector>

using namespace std;

class StringUtils {
public:
	static vector<string> splitString(string the_string, string delimiter = " ");
	static string unescapeString(const string &src);
	static string urlEncode(const string &toEncode);
};

#endif /* SRC_MAIN_UTILS_STRINGUTILS_H_ */
