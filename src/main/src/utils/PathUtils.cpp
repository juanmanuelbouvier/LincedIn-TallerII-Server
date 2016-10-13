#include <utils/PathUtils.h>

#include <utils/StringUtils.h>
#include <utils/VectorUtils.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STR_POSITION_VARIABLE_INDICATOR 0
#define PATH_VARIABLE_INDICATOR ':'


//! Get the folder path of file.
//!
//! @note example: `getFolderOfFilePath("path/to/file.ext") => "path/to"`
//!
//! @param file path string
//! @return folder path of the file path
string PathUtils::getFolderOfFilePath(const string& str) {
  size_t found;
  found = str.find_last_of("/\\");
  return str.substr(0,found);
}

//! Check if path exist in the filesystem
//!
//! @note Accepts full and relative paths.
//!
//! @param path <pathname>
//! @return true if path exists
bool PathUtils::isValidPath(string pathname) {
	if (pathname.back() != '/'){
		pathname += "/";
	}
	struct stat info;
	return (stat(pathname.c_str(), &info) == 0 && S_ISDIR(info.st_mode));
}

//! Check if sub-path name is variable.
//!
//! @param sub-path name string
//! @return if the subpath satisfy a \b PATH_VARIABLE_INDICATOR in \b STR_POSITION_VARIABLE_INDICATOR.
//! @note a sub-path is a part of path. if path is \a `"hello/world"`, the sub-paths are \a `"hello"` and \a `"world"`
bool PathUtils::isVariableSubPath( string subpath ) {
	return ( subpath[STR_POSITION_VARIABLE_INDICATOR] == PATH_VARIABLE_INDICATOR);
}


//! Convert (get) a variable sub-path in key (name).
//!
//! @note This method only remove in the string the \b PATH_VARIABLE_INDICATOR in \b STR_POSITION_VARIABLE_INDICATOR.
//!
//! @param sub-path variable string
//! @return return name of variable
string PathUtils::variableSubPathToKey( string subpath ) {
	string key = subpath;
	if ( !isVariableSubPath(subpath) ){
		return key;
	}
	key = key.erase(STR_POSITION_VARIABLE_INDICATOR,STR_POSITION_VARIABLE_INDICATOR + 1);
	return key;
}


//! Generated Regular Expression from path with or without variables
//!
//! @note Variable convention is according \b PATH_VARIABLE_INDICATOR in \b STR_POSITION_VARIABLE_INDICATOR.<BR>The Regular Expression accept query to match paths.<BR>example:<BR> `/hello/:name/:surname  =>  ^\/hello\/([^\\/]+?)\/([^\\/]+?)(?:\/(?=$))?$`.<BR>This Match `/hello/anything/anything` or `/hello/anything/anythin?anything`
//!
//! @param full path with variables
//! @return return a regular expression.
string PathUtils::generateRegexPath( string uri_path_with_variables ) {
	/*
	 *
	 *
	 */
	vector<string> splitUriPath = StringUtils::splitString(uri_path_with_variables,"/");
	string regularExpresion = "^";
	for(vector<string>::iterator it = splitUriPath.begin(); it != splitUriPath.end(); ++it) {
	    regularExpresion += "\\/";
		if ( isVariableSubPath(*it) ){
	    	regularExpresion += "([^\\/]+?)";
	    } else {
	    	regularExpresion += *it;
	    }
	}
	regularExpresion += "(?:\\/(?=$))?$";
	return regularExpresion;
}

//! Check if path match with the representative path who contains varibles
//!
//!
//! @param full path with variables
//! @param path with varible
//! @return true if match.
bool PathUtils::matchPathRegexp(string path, string uri_path_regx){
	regex regular_expresion_uri( generateRegexPath(uri_path_regx) );
	smatch base_match;
	return regex_match(path,regular_expresion_uri);
}

//! Parse route(path) respect the path with varibles
//!
//!
//! @param path to be parsed
//! @param path with varibles that represents.
//! @return map with variable values and route.
//! @note The map always contains key "_route" who is the input. If the input rout has a query the map will also contain a key "_query".<BR>If the parameters not match, the map only contains the root (and the query, if have).
//! @note Example with `hello/:first/:second`:<BR>/hello/one/two?query1=true` ==> { _route : /hello/world, _query : query1=true, first : one, second : two }
map<string,string> PathUtils::routerParser( string uriPath, string pathRegexp ){
	map<string,string> keys;

	vector<string> splitQuery = StringUtils::splitString(uriPath,"?");
	string path = splitQuery[0];
	splitQuery.erase(splitQuery.begin());
	if (splitQuery.size() > 0){
		keys["_query"] = VectorUtils::joinVector(splitQuery,"");
	}

	keys["_route"] = path;
	if ( !matchPathRegexp(uriPath,pathRegexp) ){
		return keys;
	}
	vector<string> splitedUriPath = StringUtils::splitString(path,"/");
	vector<string> splitedpathRegexp = StringUtils::splitString(pathRegexp,"/");
	string key,value,subPath;
	for (size_t i = 0; i < splitedUriPath.size(); i++) {
		subPath = splitedpathRegexp[i];
		if ( isVariableSubPath(subPath) ){
			key = variableSubPathToKey(subPath);
			value = splitedUriPath[i];
			keys[key] = value;
		}
	}
	return keys;
}
