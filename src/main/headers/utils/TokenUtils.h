#ifndef SRC_MAIN_SRC_UTILS_TOKENUTILS_H_
#define SRC_MAIN_SRC_UTILS_TOKENUTILS_H_

#include <model/User.h>

namespace std {

class TokenUtils {
public:
	static bool isValidToken(string token);
	static string generateSessionToken(string user_id);
	static User userByToken(string token);
	static string renovateToken(string token);
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_UTILS_TOKENUTILS_H_ */
