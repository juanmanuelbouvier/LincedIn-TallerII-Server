#ifndef SRC_MAIN_SRC_MODEL_FRIENDS_H_
#define SRC_MAIN_SRC_MODEL_FRIENDS_H_

#include <services/DB/DBManager.h>
#include <utils/ErrorMessage.h>
#include <extern/json.h>

using namespace std;
/**
 * Friends is a undirectional graph who contains relationships between users of the application
 */
class Friends {
private:
	static DB* getDB();
	static Json::Value getUserFriendsValue(string user_id);
	static bool storeUser(string user_id, Json::Value friend_data);
	static Json::Value generateFriendData(int state);
public:
	/**
	 * Add or, if exist accept a friend request
	 * @param source of user who send a request.
	 * @param destination user to receive a request.
	 * @return Returns an error summary, if exist any
	 */
	static ErrorMessage add(string source_user_id, string destination_user_id);

	/**
	 * List friends of a user
	 * @param user id
	 * @return Json Array who contain id of the friends
	 */
	static Json::Value listFriends(string user_id);

	/**
	 * List Pending Friend of an user (Pending is when the user still does not accept or no yet accepted)
	 * @param user id
	 * @return Json Array of users who is pending
	 */
	static Json::Value listPendingFriends(string user_id);

	/**
	 * List online friends
	 * @note Online: They did some activity in the application recently
	 * @param user id
	 * @return Json Array with friends online id
	 */
	static Json::Value listFriendsOnline(string user_id);

	/**
	 * Remove an Pending o acepted friend
	 * @param source user id
	 * @param destination user id
	 * @return Error sumary, if exist any
	 */
	static ErrorMessage remove(string source_user_id, string destination_user_id);

	/**
	 * Return status of friendly
	 * @param source user id
	 * @param destination user id
	 * @return NONE if not friendly
	 */
	static string statusFriend(string source_user_id,string destination_user_id);
};

#endif /* SRC_MAIN_SRC_MODEL_FRIENDS_H_ */
