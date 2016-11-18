#ifndef SRC_MAIN_SRC_UTILS_TOKENUTILS_H_
#define SRC_MAIN_SRC_UTILS_TOKENUTILS_H_

#include <model/User.h>

using namespace std;

class TokenUtils {
public:
	static bool isValidToken(string token);
	static string generateSessionToken(string user_id);
	static User userByToken(string token);
	static string userIDByToken(string token);
	static string renovateToken(string token);
};

#endif /* SRC_MAIN_SRC_UTILS_TOKENUTILS_H_ */
