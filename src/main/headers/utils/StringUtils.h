#ifndef SRC_MAIN_UTILS_STRINGUTILS_H_
#define SRC_MAIN_UTILS_STRINGUTILS_H_

#include <string>
#include <vector>

using namespace std;

class StringUtils {
public:
	static vector<string> splitString(string the_string, string delimiter = " ");
	static string unescapeString(const string &src);
	static string urlEncode(const string &toEncode);
	static string passwordEncrypt(string password);
	static string passwordDecrypt(string password);
	static string generateRandomPassword();
	static string replace(string original, string toReplace, string replace = "");
	static string toLowerCase(string input);
	static string toUpperCase(string input);
	static string generateFileMessage( string file, int line );
};

#endif /* SRC_MAIN_UTILS_STRINGUTILS_H_ */
