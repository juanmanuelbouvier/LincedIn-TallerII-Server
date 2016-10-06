#include <iostream>
#include "LincedInServerConfig.h"
#include "service/MongooseServer/Server.h"
#include "service/Logger/Logger.h"
#include "Utils/PathUtils.h"

#include "service/MongooseServer/ServerClient.h"
#include "service/HTTP/Message/HTTPRequest.h"
#include "service/HTTP/Message/HTTPResponse.h"

#define DEFAULT_APP_SERVER_PORT		8081
#define DEFAULT_APP_LOG_LEVEL		DEBUG
#define DEFAULT_APP_LOG_STDOUT		true
#define DEFAULT_APP_LOG_PATH		"logs/LincedInAppServer.log"

using namespace std;


int SERVER_PORT = DEFAULT_APP_SERVER_PORT;


void parseArguments(int argc, char** argv){
	int option,
		logLevel = DEFAULT_APP_LOG_LEVEL,
		serverPort = SERVER_PORT;
	string logPath = DEFAULT_APP_LOG_PATH;
	bool logStdOut = DEFAULT_APP_LOG_STDOUT;

	bool changeLogDir = false;

	string helpMSG = "==== LincedInAppServer | version: " + to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR) + " ====\n"
						"Options:\n"
						" -h \t\t\tShows help.\n"
						" -l [LOG_LEVEL]\t\tSets log level. 0 => ERROR; 1 => WARNING; 2 => INFO; 3 => DEBUG.\n"
						"\t\t\tDefault " + to_string(DEFAULT_APP_LOG_LEVEL) + "\n"
						" -w [LOG_PATH]\t\tSet Path to write log.\n"
						"\t\t\tDefault '" + DEFAULT_APP_LOG_PATH + "'\n"
						" -o [BOOL]\t\tLog in stdout. not 0 => YES; 0 => NO.\n"
						"\t\t\tDefault " + to_string(int(DEFAULT_APP_LOG_STDOUT)) + "\n"
						" -p [LISTEN_PORT]\tSets port for incomming connections.\n"
						"\t\t\tDefault " + to_string(DEFAULT_APP_SERVER_PORT) + "\n";

	while ((option = getopt(argc, argv, "hl:p:s:w:o:")) != -1)
		switch (option) {
			case 'h': {
				cout << helpMSG;
				exit(0);
				break;
			}
			case 'l': {
				int log_level = atoi(optarg);
				if (log_level >= 0 && log_level <= 3){
					logLevel = log_level;
				} else {
					cout << "Invalid Log Level (" + to_string(log_level) + "). Using Default [DEBUG:" + to_string(DEFAULT_APP_LOG_LEVEL) + "]" << endl;
				}
				break;
			}
			case 'w': {
				string log_path = string(optarg);
				string pathOfLog = PathUtils::getFolderOfFilePath(log_path) + "/";
				if ( PathUtils::isValidPath(pathOfLog) ){
					logPath = log_path;
					changeLogDir = true;
				} else {
					cout << "Invalid Log Path (folder '" + pathOfLog + "' not exist). Using Default [" + DEFAULT_APP_LOG_PATH + "]" << endl;
				}
				break;
			}
			case 'o': {
				bool log_stdout = (string(optarg) == "0") ? false : true;
				logStdOut = log_stdout;
				break;
			}
			case 'p': {
				serverPort = atoi(optarg);
				if (serverPort <= 0 || serverPort >= 48653){
					cout << "Invalid port number (" + to_string(serverPort) + "). Using Default [" + to_string(DEFAULT_APP_SERVER_PORT) + "]" << endl;
				} else {
					SERVER_PORT = serverPort;
				}
				break;
			}
			default: {
				cout << "ERROR: Invalid Arguments. See the help (-h)." << endl;
				cout << helpMSG;
				abort();
			}
		}


	if ( !changeLogDir && !PathUtils::isValidPath(PathUtils::getFolderOfFilePath(logPath) + "/") ){
		cout << "WARN: Logs directory not found (logs/). Logger work in log.log" << endl;
		logPath = "LincedInAppServer.log";
	}
	LoggerInit(logLevel, logStdOut, logPath);

	for (int index = optind; index < argc; index++)
		printf("Non-option argument %s\n", argv[index]);

}


/**
* Launchs the application server.<BR>
*/
int main(int argc, char **argv) {
	parseArguments(argc,argv);

	Server* server = new Server(SERVER_PORT);

	//TODO: Correr en otro hilo
	server->start();

	delete server;

	return 0;
}
