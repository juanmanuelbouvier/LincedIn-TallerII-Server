#include "StringUtils.h"

//! Split string by a delimiter
//!
//! @param the_string string to be splited.
//! @param delimiter used to split (default value is " ").
//! @return vector of string.
vector<string> StringUtils::splitString(string the_string, string delimiter) {
	char* string_char = const_cast<char*>(the_string.c_str());

	vector<string> splitedString;

	char* current = strtok( string_char,delimiter.c_str() );
	while(current != NULL) {
		splitedString.push_back(current);
		current = strtok( NULL,delimiter.c_str() );
	}

	return splitedString;
}

