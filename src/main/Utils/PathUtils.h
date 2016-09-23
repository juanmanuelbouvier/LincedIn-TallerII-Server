/*
 * PathUtils.h
 *
 *  Created on: 6 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_UTILS_PATHUTILS_H_
#define SRC_MAIN_UTILS_PATHUTILS_H_

#include "StringUtils.h"
#include "VectorUtils.h"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex>
#include <vector>
#include <map>

using namespace std;

string getFolderOfFilePath(const string& str);

bool isValidPath(string pathname);

vector<string> splitPath(string path, string prefix = "/");

bool isVariableSubPath( string subpath );

string variableSubPathToKey( string subpath );

string generateRegexPath( string uri_path_with_variables );

bool matchPathRegexp(string path, string uri_path_regx);

map<string,string> routerParser( string uriPath, string pathRegexp );


#endif /* SRC_MAIN_UTILS_PATHUTILS_H_ */
