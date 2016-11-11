#ifndef SRC_MAIN_SRC_UTILS_JSONUTILS_H_
#define SRC_MAIN_SRC_UTILS_JSONUTILS_H_

#include <string>
#include <list>
#include <extern/json.h>


using namespace std;

class JSONUtils {
public:
	static string JSONToString( Json::Value json );
	static Json::Value stringToJSON(string json);

	//find Value in values, if not find the "value" return nullptr
	static Json::Value findValue(Json::Value values, string key,string goal);

	static int isValueInArray( Json::Value toFind, Json::Value array );

	static Json::Value listToArrayValue(list<string> theList);
};

#endif /* SRC_MAIN_SRC_UTILS_JSONUTILS_H_ */
