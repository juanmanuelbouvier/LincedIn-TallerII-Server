#include <leveldb/db.h>
#include <services/DB/DB.h>
#include <settings/SettingManager.h>
#include <services/Logger/Logger.h>
#include <utils/JSONUtils.h>

#include <iostream>

DB::DB( string DBName ) {
	nameOfDB = DBName;
	pathToDB = SettingManager::getInstance()->getDBFolder() + "/" + nameOfDB;
	options.create_if_missing = true;
	db = NULL;
	opened = false;
}

bool DB::open() {
	string dbName = "./" + pathToDB;
	leveldb::Status status = leveldb::DB::Open(options, dbName, &db);
	if ( !status.ok() ) {
		LOG("Cannot open/create database '" + nameOfDB + "'\n\tlevelDB Status: " + status.ToString(),ERROR);
		Log("Attemp to repair it",DEBUG);
		status = leveldb::RepairDB(dbName,options);
		if (status.ok()) {
			status = leveldb::DB::Open(options, dbName, &db);
			if ( status.ok() ) {
				Log("DB " + dbName + " repaired and opened",INFO);
			}
		}
		LOG("Cannot repair " + nameOfDB,ERROR);
		return false;
	}
	Log("Succefully opened database '" + nameOfDB + "'\n\tlevelDB Status: " + status.ToString(),INFO);
	opened = true;
	return true;
}

bool DB::write(string action) {
	leveldb::Status status = db->Write(leveldb::WriteOptions(), &batchWorker);
	return ( status.ok() ) ? true : Log("Cannot " + action + " in '" + nameOfDB + "'\n levelDB Status: " + status.ToString() ,WARNING).empty();
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
	}

	return root;
}

Json::Value DB::getHigherKeyValue(int withoutTheLatters){
	Json::Value root;
	if (!opened){
		root["error"] = "cannot open DB";
		return root;
	}
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToLast();

	if (withoutTheLatters > 0) {
		for (int i = 0 ; i < withoutTheLatters && it->Valid(); i++){
			it->Prev();
		}
	}
	root["error"] = "not find key in DB";
	return ( it->Valid() ) ? JSONUtils::stringToJSON(it->value().ToString()) : root;
}

void DB::iterateAllKeyJson( void (*f)(string key, Json::Value value), Json::Value& collector ) {
	if (!opened) {
		return;
	}
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
	    string key = it->key().ToString();
	    Json::Value value = JSONUtils::stringToJSON(it->value().ToString());
	    f(key,value);
	    if (!collector.isNull()) {
	    	collector[key] = value;
	    }
	}
	delete it;
}

Json::Value DB::getAllKeys(){
	Json::Value keys(Json::arrayValue);
	if (!opened) {
		return keys;
	}
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		string key = it->key().ToString();
		keys.append(key);
	}
	delete it;
	return keys;
}

DB::~DB() {
	delete db;
}






