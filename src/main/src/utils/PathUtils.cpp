#include <utils/PathUtils.h>

#include <utils/StringUtils.h>
#include <utils/VectorUtils.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex>

#define STR_POSITION_VARIABLE_INDICATOR 0
#define PATH_VARIABLE_INDICATOR ':'



string PathUtils::getFolderOfFilePath(const string& str) {
  size_t found;
  found = str.find_last_of("/\\");
  if (int(found) == -1){
	  return "";
  }
  return str.substr(0,found);
}


bool PathUtils::isValidPath(string pathname) {
	if (pathname.back() != '/'){
		pathname += "/";
	}
	struct stat info;
	return (stat(pathname.c_str(), &info) == 0 && S_ISDIR(info.st_mode));
}


bool PathUtils::isVariableSubPath( string subpath ) {
	return ( subpath[STR_POSITION_VARIABLE_INDICATOR] == PATH_VARIABLE_INDICATOR);
}



string PathUtils::variableSubPathToKey( string subpath ) {
	string key = subpath;
	if ( !isVariableSubPath(subpath) ){
		return key;
	}
	key = key.erase(STR_POSITION_VARIABLE_INDICATOR,STR_POSITION_VARIABLE_INDICATOR + 1);
	return key;
}



string PathUtils::generateRegexPath( string uri_path_with_variables ) {
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


bool PathUtils::matchPathRegexp(string path, string uri_path_regx){
	regex regular_expresion_uri( generateRegexPath(uri_path_regx) );
	smatch base_match;
	return regex_match(path,regular_expresion_uri);
}


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
