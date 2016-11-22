#ifndef SRC_MAIN_SRC_MODEL_USERACTIVITY_H_
#define SRC_MAIN_SRC_MODEL_USERACTIVITY_H_

#include <utils/ErrorMessage.h>
#include <services/DB/DBManager.h>

using namespace std;

class UserActivity {
private:
	static DB* getDB();
public:
	static ErrorMessage recordAccess(string user_id);
};

#endif /* SRC_MAIN_SRC_MODEL_USERACTIVITY_H_ */
