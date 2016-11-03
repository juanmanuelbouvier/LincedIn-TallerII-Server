#include <services/DB/DBManager.h>
#include <leveldb/db.h>
#include <settings/SettingManager.h>
#include <services/Logger/Logger.h>
#include <utils/JSONUtils.h>

DBManager::DBManager( string DBName ) {
	nameOfDB = DBName;
	pathToDB = SettingManager::getInstance()->getDBFolder() + nameOfDB;
	options.create_if_missing = true;
	db = NULL;
	opened = false;
}

bool DBManager::open() {
	leveldb::Status status = leveldb::DB::Open(options, "./" + pathToDB, &db);
	if ( !status.ok() ) {
		Log("Unable to open/create database '" + nameOfDB + "'\n levelDB Status: " + status.ToString(),ERROR);
		return false;
	}
	Log("Succefully opened database '" + nameOfDB + "'\n levelDB Status: " + status.ToString(),INFO);
	opened = true;
	return true;
}

bool DBManager::storeJSON( string key, Json::Value json) {
	return store(key, JSONUtils::JSONToString(json));
}

bool DBManager::store( string key, string value) {
	if (!opened) {
		return false;
	}

	leveldb::WriteOptions writeOptions;
	leveldb::Status status = db->Put(writeOptions, key, value);
	if ( !status.ok() ) {
		Log("Cannot store key: " + key + " in '" + nameOfDB + "'\n levelDB Status: " + status.ToString(),WARNING);
		return false;
	}
	return true;
}

string DBManager::get( string key ){
	string returnValue = "";
	if (!opened){
		return "";
	}
	leveldb::ReadOptions readOptions;
	leveldb::Status status = db->Get(readOptions, key, &returnValue);
	if ( status.ok() ){
		return returnValue;
	}
	return "";
}

Json::Value DBManager::getJSON( string key ){
	string returnJSON = get(key);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( returnJSON.c_str(), root );

	return root;
}

DBManager::~DBManager() {
	delete db;
}






