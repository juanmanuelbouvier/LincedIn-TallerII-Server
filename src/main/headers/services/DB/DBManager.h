#ifndef SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_
#define SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_

#include <map>
#include <string>
#include <services/DB/DB.h>

using namespace std;

/**
 * DBManager is a Singleton who manage al access to de diferents Databases
 */
class DBManager {
protected:
	map<string,DB*> databases;
private:
	static DBManager* managerInstance;

public:
	DBManager(){};

	/**
	 * Get the singleton instance
	 * @return Pointer to the instance
	 */
	static DBManager* getInstance();

	/**
	 * Delete a singleton instance.
	 */
	static void deleteInstance();

	/**
	 * Add DB to the manager
	 * @param DB Name
	 * @return True if succesfull added
	 */
	bool addDB( string DBName );

	/**
	 * Check if the DB is already exist in DBManager
	 * @param DB Name
	 * @return True if exist
	 */
	bool exist( string name );

	/**
	 * Get a DB pointer from a DB Name
	 * @param DB Name
	 * @return DB Pointer
	 * @note if the DB not exist DBManager will open it.
	 */
	static DB* getDB( string DBName );

	virtual ~DBManager();
};

#endif /* SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_ */
