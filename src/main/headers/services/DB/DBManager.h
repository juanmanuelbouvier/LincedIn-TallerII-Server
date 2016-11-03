#ifndef SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_
#define SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_

#include <extern/json.h>
#include <string>
#include <leveldb/db.h>

using namespace std;

class DBManager {
private:
	string nameOfDB;
	string pathToDB;

	leveldb::DB* db;
	leveldb::Options options;

	bool opened;

public:
	DBManager( string DBName );

	bool open();

	bool store( string key, string value);
	bool storeJSON( string key, Json::Value json);

	string get( string key );
	Json::Value getJSON( string key );

	virtual ~DBManager();
};

#endif /* SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_ */
