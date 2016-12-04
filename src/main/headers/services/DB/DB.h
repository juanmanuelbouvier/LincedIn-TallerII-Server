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
	/**
	 * Create DB with name.
	 * @param Name of DB
	 * @note The files of the DB will be saved in the place that was established in the configuration (Settings).
	 */
	DB( string DBName );

	/**
	 * Open a DB
	 * @return True if the DB could be opened
	 */
	bool open();

	/**
	 * Store a string value in key.
	 * @param Key
	 * @param Value for Key
	 * @return True if Could Be stored
	 */
	bool store( string key, string value);

	/**
	 * Store a Json value in key.
	 * @param Key
	 * @param Json Value for Key
	 * @return True if Could Be stored
	 */
	bool storeJSON( string key, Json::Value json);

	/**
	 * Delete a key in the DB
	 * @param Key to be deleted
	 * @return true if successfully delete
	 * @note If the key not exist in DB. Return false
	 */
	bool Delete(string key);

	/**
	 * Get the value of a key
	 * @param key
	 * @return String value
	 * @note if Value not exist. Return empty string
	 */
	string get(string key);

	/**
	 * Get the Json value of a key
	 * @param key
	 * @return Json value
	 * @note if Value not exist. Return error member in the Json
	 */
	Json::Value getJSON(string key);

	/**
	 * Get the Higher key Value
	 * @note LevelDB has sorted store keys
	 * @param number of the ignore Latest keys
	 * @return Json value of a highest key.
	 * @note If the DB has not key or the param exced bounds. Return error member in the Json
	 */
	Json::Value getHigherKeyValue(int withoutTheLatters);

	/**
	 * Iterate all key, Value of DB. For each one, call funciotn and store in collector (if it not null)
	 * @param Void function who be called. Collector to store key,value
	 */
	void iterateAllKeyJson( void(*f)(string key, Json::Value value), Json::Value& collector );

	/**
	 * Get all keys of the DB
	 * @return Json::Value array who contains all keys
	 */
	Json::Value getAllKeys();

	/**
	 * Check if key exist in DB
	 * @param key to check
	 * @return True if exist
	 */
	bool exist(string key);

	virtual ~DB();
};

#endif /* SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_ */
