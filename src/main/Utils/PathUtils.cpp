#include "PathUtils.h"

string getFolderOfFilePath(const string& str) {
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found);
}


bool isValidPath(string pathname){
	struct stat info;
	if (stat(pathname.c_str(), &info) == 0 && S_ISDIR(info.st_mode)){
	    return true;
	}
	return false;
}
