#ifndef SRC_MAIN_UTILS_PATHUTILS_H_
#define SRC_MAIN_UTILS_PATHUTILS_H_

#include <string>
#include <regex>
#include <vector>
#include <map>

using namespace std;

class PathUtils {
public:
	static string getFolderOfFilePath(const string& str);

	static bool isValidPath(string pathname);

	static vector<string> splitPath(string path, string prefix = "/");

	static bool isVariableSubPath( string subpath );

	static string variableSubPathToKey( string subpath );

	static string generateRegexPath( string uri_path_with_variables );

	static bool matchPathRegexp(string path, string uri_path_regx);

	static map<string,string> routerParser( string uriPath, string pathRegexp );
};

#endif /* SRC_MAIN_UTILS_PATHUTILS_H_ */
