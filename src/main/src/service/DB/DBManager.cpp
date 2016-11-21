#include <services/DB/DBManager.h>
#include <exception/DBManagerException.h>
#include <services/Logger/Logger.h>
#include <exception/DBManagerException.h>

DBManager* DBManager::managerInstance = NULL;

DBManager* DBManager::getInstance(){
	if (!managerInstance) {
		managerInstance = new DBManager();
	}
	return managerInstance;
}

void DBManager::deleteInstance(){
	if (managerInstance) {
		delete managerInstance;
		managerInstance = NULL;
	}
}

bool DBManager::exist( string DBName ) {
	if ( databases.find(DBName) == databases.end() ) {
		return false;
	}
	return true;
}

bool DBManager::addDB( string DBName ) {
	bool success = false;
	if ( !exist(DBName) ) {
		DB* db = new DB(DBName);
		if ( db->open() ) {
			databases[DBName] = db;
			success = true;
		}
	}
	return success;
}

DB* DBManager::getDB( string DBName ) {
	DBManager* manager = getInstance();
	bool success = true;
	if ( !manager->exist(DBName) ) {
		Log("Database " + DBName + " It is not open. Attemp to do it", WARNING);
		success = manager->addDB(DBName);
	}
	return (success) ? manager->databases[DBName] : throw DBManagerException("Cannot open DB: " + DBName);
}

DBManager::~DBManager() {
	for(std::map<string,DB*>::iterator iter = databases.begin(); iter != databases.end(); ++iter) {
		DB* toDelete = iter->second;
		delete toDelete;
	}
}

