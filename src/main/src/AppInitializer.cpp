#include <iostream>
#include "LincedInServerConfig.h"
#include <services/Server/Server.h>
#include <settings/SettingManager.h>


#include <string>
using namespace std;

#define SETTING_FILE "settings/setting.json"

string parseArguments(int argc, char** argv){
	int option;
	string setting_file = SETTING_FILE;
	string helpMSG = "==== LincedInAppServer | version: " + to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR) + " ====\n"
						" -h Shows help.\n"
						" -s [SETTINGS FILE] path to setting file (json)\tDefault: \"" + SETTING_FILE + "\""
						"\n\n==========================================\n"
						"\nSetting JSON structure:\n{\n"
						"\tlogger: { \n"
						"\t\tlevel: type number \t\tSets log level. 0 => ERROR; 1 => WARNING; 2 => INFO; 3 => DEBUG.\n"
						"\t\tfile: type string\t\tSet Path to write log.\n"
						"\t\tshow_in_stdout: type boolean\tIf true the logs also be displayed in stdout.\n\t}\n"
						"\tport: type int\tSets port for incomming connections.\n}\n";

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



/**
* Launchs the application server.<BR>
*/
int main(int argc, char **argv) {
	string setting_file = parseArguments(argc,argv);

	SettingManager* setting = SettingManager::getInstance();
	setting->readFile(setting_file);
	setting->initLogger();

	Server* server = new Server( setting->getServerPort() );

	//TODO: Correr en otro hilo
	server->start();

	delete server;

	return 0;
}