#ifndef SRC_MAIN_SRC_UTILS_JSONUTILS_H_
#define SRC_MAIN_SRC_UTILS_JSONUTILS_H_

#include <string>
#include <extern/json.h>

using namespace std;

class JSONUtils {
public:
	static string JSONToString( Json::Value json );

};

#endif /* SRC_MAIN_SRC_UTILS_JSONUTILS_H_ */
