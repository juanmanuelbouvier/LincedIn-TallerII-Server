#include <services/DB/DBManager.h>
#include <exception/DBManagerException.h>
#include <services/Logger/Logger.h>

DBManager* DBManager::managerInstance = NULL;

DBManager* DBManager::getInstance(){
	if (!managerInstance) {
		managerInstance = new DBManager();
	}
	return managerInstance;
}

void DBManager::setInstance(DBManager* dbManager){
	if (managerInstance) {
		delete managerInstance;
	}
	managerInstance = dbManager;
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
	if ( exist(DBName) ) {
		return false;
	}
	DB* db = new DB(DBName);
	if ( db->open() ) {
		databases[DBName] = db;
		return true;
	}
	return false;
}

DB* DBManager::getDB( string DBName ) {
	DBManager* manager = getInstance();
	if ( !manager->exist(DBName) ) {
		Log("Database " + DBName + " It is not open. Attemp to do it", WARNING);
		if ( !manager->addDB(DBName) ) {
			Log("Cannot open Database: " + DBName,ERROR);
			return NULL;
		}
	}
	return manager->databases[DBName];
}

DBManager::~DBManager() {
	for(std::map<string,DB*>::iterator iter = databases.begin(); iter != databases.end(); ++iter) {
		DB* toDelete = iter->second;
		delete toDelete;
	}
}

