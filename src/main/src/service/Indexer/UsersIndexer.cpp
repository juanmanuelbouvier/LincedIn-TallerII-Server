#include <services/Indexer/UsersIndexer.h>
#include <services/DB/DBManager.h>
#include <services/Logger/Logger.h>
#include <services/Search/ElasticClient.h>

Json::Value UsersIndexer::fusion(Json::Value old, Json::Value neew) {
	Json::Value theFusion;
	for ( auto key : old.getMemberNames() ) {
		theFusion[key] = old[key];
	}
	for ( auto key : neew.getMemberNames() ) {
		theFusion[key] = neew[key];
	}
	return theFusion;
}

Json::Value cleanData(Json::Value data) {
	data.removeMember("date_of_birth");
	data.removeMember("last_edit_timestamp");
	data.removeMember("password");
	data.removeMember("register_timestamp");
	return data;
}
void UsersIndexer::collect(string user_id, Json::Value data) {
	ElasticClient e;
	Json::Value last = e.get("lincedin","user","user_id");
	string action = "Added";
	data = cleanData(data);
	if ( !last.isNull() ) {
		data = fusion(last,data);
		action = "Updated";
	}
	if ( e.index("lincedin","user",user_id,data) ) {
		Log(action + " user " + user_id + " to index DB",DEBUG);
	} else {
		Log("Cannot index user " + user_id + " to index DB",WARNING);
	}
}

void UsersIndexer::index() {
	Log("Attemp to index User Database",INFO);
	ElasticClient e;
	if (!e.isAlive() ) {
		Log("Cannot index DB Users. Elastic client is close", WARNING);
		return;
	}

	Json::Value dummy(Json::nullValue);
	Log("Start to index DB Users",INFO);
	DBManager::getInstance()->getDB("User")->iterateAllKeyJson(collect,dummy);
	Log("Finished Indexing on DB User",INFO);

	Log("Start to index DB Skills",INFO);
	DBManager::getInstance()->getDB("Skills")->iterateAllKeyJson(collect,dummy);
	Log("Finished Indexing on DB Skills",INFO);
	DBManager::deleteInstance();

}
