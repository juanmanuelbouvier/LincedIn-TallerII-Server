#ifndef SRC_MAIN_UTILS_STRINGUTILS_H_
#define SRC_MAIN_UTILS_STRINGUTILS_H_

#include <string>
#include <vector>

using namespace std;

class StringUtils {
public:
	/**
	 * Split string by a delimiter
	 * @param the_string string to be splited.
	 * @param delimiter used to split (default value is " ").
	 * @return vector of string.
	 */
	static vector<string> splitString(string the_string, string delimiter = " ");

	/**
	 * @author CGICPP
	 * Convert encoded characters in form data to normal ASCII.
	 * <P>For example, %21 is converted to ! and + is converted to a space.
	 * Normally, this is called internally to decode the query string or post
	 * data.</P>
	 * @param src The src string containing the encoded characters
	 * @return The converted string
	 */
	static string unescapeString(const string &src);

	/**
	 * Reverse work that makes unescapeString
	 * @param src The src string containing the encode characters
	 * @return The converted string
	 */
	static string urlEncode(const string &toEncode);

	/**
	 * Encrypt string
	 * @params The string/password to be encrypted
	 * @return The encrypted string
	 */
	static string passwordEncrypt(string password);

	/**
	 * Decrypt string who be encrypted.
	 * @params The string/password encrypted
	 * @return The original string
	 */
	static string passwordDecrypt(string password);

	/**
	 * Generate random string with length PASSWORD_LEN and PASSWORD_CHARS chars.
	 * @return Random string.
	 */
	static string generateRandomPassword();

	/**
	 * Replace a substring in a string.
	 * @param Original string
	 * @param The substring to be replace
	 * @param The replace string.
	 * @return Original string with substring replaced.
	 * ej. replace("hello world","ll","r") ==> hero world
	 */
	static string replace(string original, string toReplace, string replace = "");

	/**
	 * Transform string to lower case.
	 * @param The string to be transformed
	 * @return The input param in lower case
	 * ej. toLowerCase("HellO WorLd") ==> hello world
	 */
	static string toLowerCase(string input);

	/**
	 * Transform string to upper case.
	 * @param The string to be transformed
	 * @return The input param in upper
	 * ej. toLowerCase("HellO WorLd") ==> HELLO WORLD
	 */
	static string toUpperCase(string input);

	/*
	 * Generate a pretty message from a file and line.
	 * ej generateFileMessage("home/user/src/main/Text/text.cpp",245) ==> "main/Text/text.cpp::245"
	 */
	static string generateFileMessage( string file, int line );
};

#endif /* SRC_MAIN_UTILS_STRINGUTILS_H_ */
