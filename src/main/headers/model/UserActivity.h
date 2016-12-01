#ifndef SRC_MAIN_SRC_MODEL_USERACTIVITY_H_
#define SRC_MAIN_SRC_MODEL_USERACTIVITY_H_

#include <utils/ErrorMessage.h>
#include <services/DB/DBManager.h>

using namespace std;
/**
 * User Activity store last activity time of user to check if online in the Application
 */
class UserActivity {
private:
	static DB* getDB();
public:
	/**
	 * Record user acces in the server.
	 * @param user id who do an action
	 * @return Error Message who contains error, if exist any
	 */
	static ErrorMessage recordAccess(string user_id);
	/**
	 * Get las time activity of user in the platform
	 * @param user id
	 * @return timestamp of the last activity
	 */
	static int getLastAccessTimestamp(string user_id);
	/**
	 * Check if user is online respect of timestamp of las activity
	 * @note Only check if the date of last activity if in range with now and SECONDS_OFFSET_ONLINE
	 * @param user id
	 * @return True if user is online on the server
	 */
	static bool isOnline(string user_id);
};

#endif /* SRC_MAIN_SRC_MODEL_USERACTIVITY_H_ */
