#ifndef SRC_MAIN_UTILS_PATHUTILS_H_
#define SRC_MAIN_UTILS_PATHUTILS_H_

#include <string>
#include <vector>
#include <map>

using namespace std;

class PathUtils {
public:
	//! Get the folder path of file.
	//!
	//! @note example: `getFolderOfFilePath("path/to/file.ext") => "path/to"`
	//!
	//! @param file path string
	//! @return folder path of the file path
	static string getFolderOfFilePath(const string& str);

	//! Check if path exist in the filesystem
	//!
	//! @note Accepts full and relative paths.
	//!
	//! @param path <pathname>
	//! @return true if path exists
	static bool isValidPath(string pathname);

	//! Check if sub-path name is variable.
	//!
	//! @param sub-path name string
	//! @return if the subpath satisfy a \b PATH_VARIABLE_INDICATOR in \b STR_POSITION_VARIABLE_INDICATOR.
	//! @note a sub-path is a part of path. if path is \a `"hello/world"`, the sub-paths are \a `"hello"` and \a `"world"`
	static bool isVariableSubPath( string subpath );

	//! Convert (get) a variable sub-path in key (name).
	//!
	//! @note This method only remove in the string the \b PATH_VARIABLE_INDICATOR in \b STR_POSITION_VARIABLE_INDICATOR.
	//!
	//! @param sub-path variable string
	//! @return return name of variable
	static string variableSubPathToKey( string subpath );

	//! Generated Regular Expression from path with or without variables
	//!
	//! @note Variable convention is according \b PATH_VARIABLE_INDICATOR in \b STR_POSITION_VARIABLE_INDICATOR.<BR>The Regular Expression accept query to match paths.<BR>example:<BR> `/hello/:name/:surname  =>  ^\/hello\/([^\\/]+?)\/([^\\/]+?)(?:\/(?=$))?$`.<BR>This Match `/hello/anything/anything` or `/hello/anything/anythin?anything`
	//!
	//! @param full path with variables
	//! @return return a regular expression.
	static string generateRegexPath( string uri_path_with_variables );

	//! Check if path match with the representative path who contains varibles
	//!
	//!
	//! @param full path with variables
	//! @param path with varible
	//! @return true if match.
	static bool matchPathRegexp(string path, string uri_path_regx);

	//! Parse route(path) respect the path with varibles
	//!
	//!
	//! @param path to be parsed
	//! @param path with varibles that represents.
	//! @return map with variable values and route.
	//! @note The map always contains key "_route" who is the input. If the input rout has a query the map will also contain a key "_query".<BR>If the parameters not match, the map only contains the root (and the query, if have).
	//! @note Example with `hello/:first/:second`:<BR>/hello/one/two?query1=true` ==> { _route : /hello/world, _query : query1=true, first : one, second : two }
	static map<string,string> routerParser( string uriPath, string pathRegexp );
};

#endif /* SRC_MAIN_UTILS_PATHUTILS_H_ */
