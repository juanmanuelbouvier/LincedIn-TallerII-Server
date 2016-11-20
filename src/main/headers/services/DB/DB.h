#ifndef SRC_MAIN_SRC_SERVICE_DB_DB_H_
#define SRC_MAIN_SRC_SERVICE_DB_DB_H_

#include <extern/json.h>
#include <string>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

using namespace std;

class DB {
private:
	string nameOfDB;
	string pathToDB;

	leveldb::DB* db;
	leveldb::Options options;
	leveldb::WriteBatch batchWorker;

	bool opened;

	bool write(string action);

public:
	DB( string DBName );

	bool open();

	bool store( string key, string value);
	bool storeJSON( string key, Json::Value json);

	bool Delete(string key);

	string get(string key);
	Json::Value getJSON(string key);
	Json::Value getHigherKeyValue(int withoutTheLatters);

	bool exist(string key);

	virtual ~DB();
};

#endif /* SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_ */
