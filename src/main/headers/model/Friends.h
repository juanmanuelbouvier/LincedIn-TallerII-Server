#ifndef SRC_MAIN_SRC_MODEL_FRIENDS_H_
#define SRC_MAIN_SRC_MODEL_FRIENDS_H_

#include <services/DB/DBManager.h>
#include <utils/ErrorMessage.h>
#include <extern/json.h>

using namespace std;

class Friends {
private:
	static DB* getDB();
	static Json::Value getUserFriendsValue(string user_id);
	static bool storeUser(string user_id, Json::Value friend_data);
	static Json::Value generateFriendData(int state);
public:
	static ErrorMessage add(string source_user_id, string destination_user_id);
	static ErrorMessage accept(string source_user_id, string destination_user_id);
	static Json::Value listFriends(string user_id);
	static Json::Value listPendingFriends(string user_id);
	static ErrorMessage remove(string source_user_id, string destination_user_id);
};

#endif /* SRC_MAIN_SRC_MODEL_FRIENDS_H_ */
