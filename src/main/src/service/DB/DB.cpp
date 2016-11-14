#include <leveldb/db.h>
#include <services/DB/DB.h>
#include <settings/SettingManager.h>
#include <services/Logger/Logger.h>
#include <utils/JSONUtils.h>

DB::DB( string DBName ) {
	nameOfDB = DBName;
	pathToDB = SettingManager::getInstance()->getDBFolder() + "/" + nameOfDB;
	options.create_if_missing = true;
	db = NULL;
	opened = false;
}

bool DB::open() {
	leveldb::Status status = leveldb::DB::Open(options, "./" + pathToDB, &db);
	if ( !status.ok() ) {
		Log("Unable to open/create database '" + nameOfDB + "'\n levelDB Status: " + status.ToString(),ERROR);
		return false;
	}
	Log("Succefully opened database '" + nameOfDB + "'\n levelDB Status: " + status.ToString(),INFO);
	opened = true;
	return true;
}

bool DB::storeJSON( string key, Json::Value json) {
	return store(key, JSONUtils::JSONToString(json));
}

bool DB::store( string key, string value) {
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

string DB::get( string key ){
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

Json::Value DB::getJSON( string key ){
	string returnJSON = get(key);
	Json::Value root;
	if (returnJSON.compare("")){
		root["error"] = "not find key in DB";
	} else {
		Json::Reader* reader = new Json::Reader();
		bool parsingSuccessful = reader->parse( returnJSON.c_str(), root );
		if (!parsingSuccessful){
			root["error"] = "error on parse value of key.";
		}
		delete reader;
	}
	return root;
}

DB::~DB() {
	delete db;
}






