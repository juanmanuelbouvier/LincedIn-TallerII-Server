#include <utils/StringUtils.h>

#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cctype>

#define PASSWORD_CHARS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define PASSWORD_LEN 8

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

/**
 * @author CGICPP
 * Convert a hex-encoded character to its ASCII equivalent.
 * <P>For example, after the call
 * <PRE class="code">
 * . char c = hexToChar('2', '1');
 * </PRE>
 * <TT>c</TT> will have a value of  '!'.</P>
 * <P>Normally, this is called internally to decode encoded characters in
 * the query string or post data.</P>
 * @param first The first character of the hex value
 * @param second the second character of the hex value
 * @return The ASCII character
 */
char hexToChar(char first, char second) {
  char digit;
  digit = (first >= 'A' ? ((first & 0xDF) - 'A') + 10 : (first - '0'));
  digit *= 16;
  digit += (second >= 'A' ? ((second & 0xDF) - 'A') + 10 : (second - '0'));
  return digit;
}



/**
 * @author CGICPP
 * Convert a ASCII character to its hex-encoded equivalent.
 * @param char to be converted
 * @return Hexa value in string
 */
string charToHex(unsigned char c) {
	short i = c;

	std::stringstream s;

	s << "%" << std::setw(2) << std::setfill('0') << std::hex << i;

	return s.str();
}

/**
 * @author CGICPP
 * Convert encoded characters in form data to normal ASCII.
 * <P>For example, %21 is converted to ! and + is converted to a space.
 * Normally, this is called internally to decode the query string or post
 * data.</P>
 * @param src The src string containing the encoded characters
 * @return The converted string
 */
string StringUtils::unescapeString(const string &src) {
  string result;
  string::const_iterator iter;
  char c;

  for(iter = src.begin(); iter != src.end(); ++iter) {
    switch(*iter) {
    case '+':
      result.append(1, ' ');
      break;
    case '%':
      c = *++iter;
      result.append(1, hexToChar(c, *(++iter)));
      break;
    default:
      result.append(1, *iter);
      break;
    }
  }

  return result;
}

/**
 * Reverse work that makes unescapeString
 * @param src The src string containing the encode characters
 * @return The converted string
 */
string StringUtils::urlEncode(const string &toEncode) {
	std::ostringstream out;

	for(std::string::size_type i=0; i < toEncode.length(); ++i) {
		short t = toEncode.at(i);
		if(
				t == 45 ||          	// hyphen
				(t >= 48 && t <= 57) || // 0-9
				(t >= 65 && t <= 90) || // A-Z
				t == 95 ||          	// underscore
				(t >= 97 && t <= 122) ||// a-z
				t == 126            	// tilde
		) {
			out << toEncode.at(i);
		} else {
			out << charToHex(toEncode.at(i));
		}
	}

	return out.str();
}

string StringUtils::generateRandomPassword() {
	string password;
	for (int i = 0; i < PASSWORD_LEN; i++) {
		char c = PASSWORD_CHARS[rand() % (sizeof(PASSWORD_CHARS) - 1)];
		password.push_back(c);
	}
	return password;
}

string StringUtils::passwordEncrypt(string password){
	return password;
}
string StringUtils::passwordDecrypt(string password){
	return password;
}

string StringUtils::replace(string original, string toReplace, string theReplace) {
	string result = original;
	size_t index = 0;
	size_t size = theReplace.size();
	if (original == toReplace) {
		return theReplace;
	}
	if (toReplace.size() == 0) {
		return result;
	}
	while (true) {
	     index = result.find(toReplace, index);
	     if (index >= result.size()) break;
	     if (size == 0) {
	    	 result.erase(index, 1);
	     } else {
	    	 result.replace(index, size, theReplace);
	     }
	     index += size;
	}
	return result;

}
string StringUtils::toLowerCase(string input) {
	string result = input;
	transform(result.begin(), result.end(), result.begin(), (int (*)(int))tolower);
	return result;
}
string StringUtils::toUpperCase(string input) {
	string result = input;
	transform(result.begin(), result.end(), result.begin(), (int (*)(int))toupper);
	return result;
}

string StringUtils::generateFileMessage( string file, int line ) {
	file.erase(0,file.find("main/"));
	return file + "::" + to_string(line);
}
