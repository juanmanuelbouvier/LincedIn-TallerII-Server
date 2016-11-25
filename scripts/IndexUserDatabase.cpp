#include <services/DB/DBManager.h>
#include <services/Searcher/ElasticClient.h>
#include <settings/SettingManager.h>
#include <iostream>
#include <extern/json.h>
#include <services/Logger/Logger.h>
#include <fstream>
using namespace std;

void setDBFolder(string folder) {
	Json::Value setting;
	setting["db_folder"] = folder;
	Json::Value logger;
	logger["level"] = 3;
	logger["show_in_stout"] = true;
	logger["file"] = "scripts/IndexUserDatabase.log";
	setting["logger"] = logger;
	ofstream out("settings/setting-indexDB.json");
	out << setting.toStyledString();
	out.close();
	SettingManager::getInstance()->readFile("settings/setting-indexDB.json");
	SettingManager::getInstance()->initLogger();
}

Json::Value fusion(Json::Value old, Json::Value neew) {
	Json::Value theFusion;
	for ( auto key : old.getMemberNames() ) {
		theFusion[key] = old[key];
	}
	for ( auto key : neew.getMemberNames() ) {
		theFusion[key] = neew[key];
	}
	return theFusion;
}

void collect(string user_id, Json::Value data) {
	ElasticClient e("localhost:9200");
	Json::Value last = e.get("lincedin","user","user_id");
	string action = "Added";
	if ( !last.isNull() ) {
		data = fusion(last,data);
		action = "Updated";
	}
	if ( e.index("lincedin","user",user_id,data) ) {
		Log(action + " user " + user_id + " to index DB",WARNING);
	} else {
		Log("Cannot index user " + user_id + " to index DB",INFO);
	}
}

int main(int argc, char **argv) {
	string db = "db";
	if ( argc < 2 ) {
		cout << "No DB folder in arguments using default: " << db << endl;
	} else {
		db = string(argv[1]);
	}
	setDBFolder(db);

	ElasticClient e("localhost:9200");
	if (!e.isAlive()){
		Log("Elastic is offline. Start it to index.",ERROR);
		return 0;
	}


	Json::Value dummy(Json::nullValue);
	Log("Start to index DB Users",INFO);
	DBManager::getInstance()->getDB("User")->iterateAllKeyJson(collect,dummy);
	Log("Finished Indexing on DB User",INFO);

	Log("Start to index DB Skills",INFO);
	DBManager::getInstance()->getDB("Skills")->iterateAllKeyJson(collect,dummy);
	Log("Finished Indexing on DB Skills",INFO);
	DBManager::deleteInstance();
	return 0;
}


