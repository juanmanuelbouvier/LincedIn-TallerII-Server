#include <services/Access/AccessLog.h>
#include <model/UserActivity.h>
#include <utils/ErrorMessage.h>

using namespace std;

void AccessLog::accessLog(Json::Value data){

	if (data.isMember("user_id")){
		recordUserAccess(data["user_id"].asString());
	}

	if (data.isMember("geolocation")){
		//record geolocation
	}

}


bool AccessLog::recordUserAccess(string user_id){
	ErrorMessage error = UserActivity::recordAccess(user_id);

	if (error)
		return false;

	return true;
}
