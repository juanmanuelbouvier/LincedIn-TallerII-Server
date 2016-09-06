/*
 * PathUtils.h
 *
 *  Created on: 6 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_UTILS_PATHUTILS_H_
#define SRC_MAIN_UTILS_PATHUTILS_H_

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

string getFolderOfFilePath(const string& str);

bool isValidPath(string pathname);


#endif /* SRC_MAIN_UTILS_PATHUTILS_H_ */
