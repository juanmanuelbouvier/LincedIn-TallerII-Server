#include "LincedInServerConfig.h"
#include <services/Server/Server.h>
#include <settings/SettingManager.h>
#include <services/DB/DBManager.h>
#include <services/SharedServerAPI/SharedServerAPI.h>
#include <utils/ThreatUtils.h>
#include <exception/AppServerException.h>

#include <iostream>
#include <string>

using namespace std;

#define SETTING_FILE "settings/setting.json"

string CLOSE_FINISH;
bool CLOSE_SIGINT = false;
void closeSignal(int signal) {
	istringstream oss("\n");
	cin.rdbuf(oss.rdbuf());
	CLOSE_SIGINT = true;
}

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
	signal(SIGINT, closeSignal);
	while (CLOSE_FINISH != "exit" && !CLOSE_SIGINT) {
		getline(cin, CLOSE_FINISH);
	}

	Server* theServer = (Server*)server;
	theServer->stop();
	return NULL;
}

void cleanMemory() {
	SettingManager::deleteInstance();
	DBManager::deleteInstance();
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
	} catch (AppServerException& e) {
		cleanMemory();
		return 0;
	}

	ThreatUtils::startThreath(closeServerWithInput, server);
	server->start();


	delete server;
	cleanMemory();
	return 0;
}
