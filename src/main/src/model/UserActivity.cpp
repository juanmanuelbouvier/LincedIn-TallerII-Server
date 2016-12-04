#include <model/UserActivity.h>
#include <model/User.h>
#include <utils/DateUtils.h>
#include <extern/json.h>
#include <services/Logger/Logger.h>
#include <services/DB/DBs.h>

#define SECONDS_OFFSET_ONLINE 2*60 //2 minutes

using namespace std;

DB* UserActivity::getDB(){
	return DBManager::getDB(Databases::DB_USER_ACTIVITY);
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


int UserActivity::getLastAccessTimestamp(string user_id){
	Json::Value userActivity = getDB()->getJSON(user_id);

	if (userActivity.isMember("error")){
		return -1;
	}

	return userActivity["last_access_timestamp"].asInt();
}

bool UserActivity::isOnline(string user_id){
	if (getLastAccessTimestamp(user_id) >= (DateUtils::timestamp() - SECONDS_OFFSET_ONLINE)){
		return true;
	}

	return false;
}
