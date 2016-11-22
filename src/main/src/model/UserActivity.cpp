#include <model/UserActivity.h>
#include <model/User.h>
#include <utils/DateUtils.h>
#include <extern/json.h>

#define USER_ACTIVITY_DB "UserActivity"

using namespace std;

DB* UserActivity::getDB(){
	return DBManager::getDB(USER_ACTIVITY_DB);
}

ErrorMessage UserActivity::recordAccess(string user_id){
	ErrorMessage error;

	if (!User::exist(user_id)){
		error.addError("user_id","user " + user_id + " not exist.");
		return error;
	}

	Json::Value data;
	data["last_access_timestamp"] = DateUtils::timestamp();

	getDB()->storeJSON(user_id,data);

	return error;
}
