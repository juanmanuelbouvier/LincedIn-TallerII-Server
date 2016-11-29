#ifndef SRC_MAIN_SRC_SERVICE_INDEXER_USERSINDEXER_H_
#define SRC_MAIN_SRC_SERVICE_INDEXER_USERSINDEXER_H_

#include <string>
#include <extern/json.h>

using namespace std;

/**
 * Index all information of users with elastic search.
 */
class UsersIndexer {
private:
	static Json::Value fusion(Json::Value old, Json::Value neew);
	static void collect(string key, Json::Value value);
public:
	/**
	 * Index all users.
	 * @note If the elastic client is close, the work will be canceled and only log an error
	 */
	static void index();
};

#endif /* SRC_MAIN_SRC_SERVICE_INDEXER_USERSINDEXER_H_ */
