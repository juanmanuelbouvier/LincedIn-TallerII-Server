#ifndef SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_
#define SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_

#include <map>
#include <string>
#include <services/DB/DB.h>

using namespace std;

class DBManager {
protected:
	map<string,DB*> databases;
private:
	static DBManager* managerInstance;

public:
	DBManager(){};

	static DBManager* getInstance();
	static void setInstance( DBManager* manager );
	static void deleteInstance();

	bool addDB( string DBName );
	bool exist( string name );
	static DB* getDB( string DBName );

	virtual ~DBManager();
};

#endif /* SRC_MAIN_SRC_SERVICE_DB_DBMANAGER_H_ */
