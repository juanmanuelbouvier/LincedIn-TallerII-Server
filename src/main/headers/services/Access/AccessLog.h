#ifndef SRC_MAIN_SRC_SERVICE_HANDLERS_ACCESSLOG_H_
#define SRC_MAIN_SRC_SERVICE_HANDLERS_ACCESSLOG_H_

#include <extern/json.h>

using namespace std;

class AccessLog {
private:
	static bool recordUserAccess(string user_id);
public:
	/**
	 * Record a Log of user in db
	 * @param Json Data.
	 * @note the data must contain user_id
	 */
	static void accessLog(Json::Value data);
};

#endif /* SRC_MAIN_SRC_SERVICE_HANDLERS_ACCESSLOG_H_ */
