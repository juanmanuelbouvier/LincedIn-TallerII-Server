#ifndef SRC_MAIN_SRC_SERVICE_INDEXER_USERSINDEXER_H_
#define SRC_MAIN_SRC_SERVICE_INDEXER_USERSINDEXER_H_

#include <string>
#include <extern/json.h>

using namespace std;

class UsersIndexer {
private:
	static Json::Value fusion(Json::Value old, Json::Value neew);
	static void collect(string key, Json::Value value);
public:
	//Interface for threads
	static void index();
};

#endif /* SRC_MAIN_SRC_SERVICE_INDEXER_USERSINDEXER_H_ */
