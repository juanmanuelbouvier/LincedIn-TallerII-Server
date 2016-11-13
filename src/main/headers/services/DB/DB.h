#ifndef SRC_MAIN_SRC_SERVICE_DB_DB_H_
#define SRC_MAIN_SRC_SERVICE_DB_DB_H_

#include <extern/json.h>
#include <string>
#include <leveldb/db.h>

using namespace std;

class DB {
private:
	string nameOfDB;
	string pathToDB;

	leveldb::DB* db;
	leveldb::Options options;

	bool opened;

public:
	DB( string DBName );

	bool open();

	bool store( string key, string value);
	bool storeJSON( string key, Json::Value json);

	string get( string key );
	Json::Value getJSON( string key );

	virtual ~DB();
};

#endif /* SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_ */
