#ifndef SRC_MAIN_SRC_UTILS_JSONUTILS_H_
#define SRC_MAIN_SRC_UTILS_JSONUTILS_H_

#include <string>
#include <list>
#include <extern/json.h>


using namespace std;

class JSONUtils {
public:
	/**
	 * Convert Json Value to String/File content.
	 * @param Value to be converted
	 * @raturn Json in string ignoring line breaks and spaces. If fails return empty string.
	 */
	static string JSONToString( Json::Value json );

	/**
	 * Convert String/File content to Json::Value
	 * @param string who contains raw json.
	 * @raturn Json Value. If de reader fail, the Value contains an "error" tag.
	 */
	static Json::Value stringToJSON(string json);

	/**
	 * Find Value into Values array.
	 * @param Array of values. Like [{ }, { }, { }, ... ]
	 * @param Key/Member to find goal into value
	 * @param Goal to find.
	 * @return Json::Value who contains value[key] == goal
	 */
	static Json::Value findValue(Json::Value values, string key,string goal);

	/**
	 * Find Value in array.
	 * @param Value to find. Can be a literal value (int or string)
	 * @param An array to search
	 * @return position of value in array
	 */
	static int isValueInArray( Json::Value toFind, Json::Value array );

	/**
	 * Convert list of string to Json Arrays who contains Json string Values.
	 * @param Array to be converted
	 * @return Json Array who contains the values of a input list
	 */
	static Json::Value listToArrayValue(list<string> theList);

	/**
	 * Convert a query type string (like. a=b&c=d&g=h..) to Json Value.
	 * @note If a param has two values. Would be an array.
	 * @param String query
	 * @return Json Array who contains the params of query
	 * ej. queryToJson("a=b&c=d&c=h") ==> { a:b, c:[d,h] }
	 */
	static Json::Value queryToJson( string query );
};

#endif /* SRC_MAIN_SRC_UTILS_JSONUTILS_H_ */
