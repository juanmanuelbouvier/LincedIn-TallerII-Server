#include "LincedInServerConfig.h"
#include <services/Logger/Logger.h>
#include <services/Server/Server.h>
#include <settings/SettingManager.h>
#include <services/DB/DBManager.h>
#include <utils/ThreatUtils.h>
#include <exception/AppServerException.h>
#include <services/Indexer/UsersIndexer.h>

#include <iostream>
#include <string>

using namespace std;

#define SETTING_FILE "settings/setting.json"

string parseArguments(int argc, char** argv){
	int option;
	string setting_file = SETTING_FILE;
	string helpMSG = "==== LincedInAppServer | version: " + to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR) + " ====\n"
						" -h Shows help.\n"
						" -s [SETTINGS FILE] path to setting file (json)\tDefault: \"" + SETTING_FILE + "\""
						"\n\n==========================================\n\n";
	helpMSG += SettingManager::getInstance()->getJSONStructure();


	while ((option = getopt(argc, argv, "hs:")) != -1)
		switch (option) {
			case 'h': {
				cout << helpMSG;
				exit(0);
				break;
			}
			case 's': {
				setting_file = string(optarg);
				break;
			}
			default: {
				cout << "ERROR: Invalid Arguments. See the help (-h)." << endl;
				exit(0);
			}
		}


	for (int index = optind; index < argc; index++)
		printf("Non-option argument %s\n", argv[index]);


	return setting_file;

}

void* closeServerWithInput(void* server) {
	string closeFinish;
	while (closeFinish != "exit") {
		getline(cin, closeFinish);
	}

	Server* theServer = (Server*)server;
	theServer->stop();
	return NULL;
}

bool CLOSE_SIGINT = false;
void closeSignal(int signal) {
	istringstream oss("\n");
	cin.rdbuf(oss.rdbuf());
	CLOSE_SIGINT = true;
}

void* closeWithSIGINT( void* server ) {
	signal(SIGINT, closeSignal);
	while (!CLOSE_SIGINT) {
		sleep(0.5);
	}
	cout << " <=== SIGINT Signal detected" << endl;
	Server* theServer = (Server*)server;
	theServer->stop();
	return NULL;
}

void* callIndexers( void* data ) {
	sleep(60);
	while (true) {
		UsersIndexer::index();
		sleep(60*20);
	}

	return NULL;
}

void* logLive( void* data ) {
	Server* server = (Server*)data;
	while (true) {
		sleep(60*60);
		Log("Server info: " + server->getStats(),INFO);
	}
	return NULL;
}

void cleanMemory() {
	SettingManager::deleteInstance();
	DBManager::deleteInstance();
}

void OpenAllDatabases() {
	if (!DBManager::startAllDBs()){
		throw AppServerException("Cannot Start DBManager. Check the permissions of " + SettingManager::getInstance()->getDBFolder() + " folder."
				" (try chmod 776 on db folder)");
	}
}

/**
* Launchs the application server.<BR>
*/
int main(int argc, char **argv) {
	string setting_file = parseArguments(argc,argv);

	SettingManager* setting = SettingManager::getInstance();
	setting->readFile(setting_file);
	setting->initLogger();

	Server* server;
	try {
		server = new Server( setting->getServerPort() );
		string version = to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR);
		Log("------------------------------------------------------------------",INFO);
		Log("\t\tNew Run of: LincedInAppServer | Version: " + version,INFO);
		Log("------------------------------------------------------------------",INFO);
		OpenAllDatabases();
		ThreatUtils::startThreath(closeServerWithInput, server);
		ThreatUtils::startThreath(closeWithSIGINT, server);
		ThreatUtils::startThreath(callIndexers,NULL);
		ThreatUtils::startThreath(logLive,server);
		server->start();
	} catch (AppServerException& e) {
		Log("The server must be close because:\n" + string(e.what()) ,ERROR);
		cleanMemory();
		return 0;
	} catch (...) {
		Log("The server must be close because (unexpected exception)",ERROR);
		cleanMemory();
		return 0;
	}


	delete server;
	cleanMemory();

	return 0;
}
