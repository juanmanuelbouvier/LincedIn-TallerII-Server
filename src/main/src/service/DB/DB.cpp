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

bool DB::write(string action) {
	leveldb::Status status = db->Write(leveldb::WriteOptions(), &batchWorker);
	if ( !status.ok() ) {
		Log("Cannot " + action + " in '" + nameOfDB + "'\n levelDB Status: " + status.ToString(),WARNING);
		return false;
	}
	return true;
}

bool DB::Delete(string key) {
	if (!opened || !exist(key)) {
		return false;
	}
	leveldb::WriteOptions writeOptions;
	batchWorker.Delete(key);
	return write("delete key: " + key);
}

bool DB::storeJSON( string key, Json::Value json) {
	return store(key, JSONUtils::JSONToString(json));
}

bool DB::store( string key, string value) {
	if (!opened) {
		return false;
	}
	leveldb::WriteOptions writeOptions;
	batchWorker.Put(key,value);
	return write("store key: " + key);
}

bool DB::exist(string key) {
	return !get(key).empty();
}

string DB::get( string key ) {
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
	if (returnJSON.empty()){
		root["error"] = "not find key in DB";
	} else {
		root = JSONUtils::stringToJSON(returnJSON);
		if ( root.isMember("error") ) {
			root["error"] = "error on parse value of key.";
		}
		/*Json::Reader* reader = new Json::Reader();
		bool parsingSuccessful = reader->parse( returnJSON.c_str(), root );
		if (!parsingSuccessful){
			root["error"] = "error on parse value of key.";
		}
		delete reader;*/
	}

	return root;
}

Json::Value DB::getHigherKeyValue(){
	Json::Value root;
	if (!opened){
		root["error"] = "cannot open DB";
		return root;
	}
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToLast();

	string res = ( it->Valid() ) ? it->key().ToString() : "";

	if (res.empty()){
		root["error"] = "not find key in DB";
	} else {
		root = JSONUtils::stringToJSON(res);
		if ( root.isMember("error") ) {
			root["error"] = "error on parse value of key.";
		}
	}

	return root;
}

DB::~DB() {
	delete db;
}






