#ifndef SRC_MAIN_SRC_UTILS_TOKENUTILS_H_
#define SRC_MAIN_SRC_UTILS_TOKENUTILS_H_

#include <model/User.h>

using namespace std;

class TokenUtils {
public:
	/**
	 * Check if token is valid.
	 * @param token
	 * @retun true if is valid
	 */
	static bool isValidToken(string token);

	/**
	 * Generate session token for user id
	 * @param User ID
	 * @return Temporary token for user id.
	 */
	static string generateSessionToken(string user_id);

	/**
	 * Get User from a token.
	 * @param token
	 * @return User. If token is invalid throw an exception
	 */
	static User userByToken(string token);

	/**
	 * Get User id from a token.
	 * @param token
	 * @return User id. If token is invalid throw an exception
	 */
	static string userIDByToken(string token);

	/**
	 * Extend the finish date of a valid Token
	 * @param token
	 * @return New token with new finish date.
	 */
	static string renovateToken(string token);
};

#endif /* SRC_MAIN_SRC_UTILS_TOKENUTILS_H_ */
