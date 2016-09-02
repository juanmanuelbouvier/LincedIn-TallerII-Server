#include <iostream>
#include "LincedInServerConfig.h"
#include "MongooseServer/Server.h"
#include "Logger/Logger.h"

using namespace std;

/**
* Launchs the application server.<BR>
* Prints the app-server version.
*/
int main(int argc, char **argv) {
	//TODO: Parser para puerto y logLevel

	LoggerInit(DEBUG, true, "log.log");

	Server* server = new Server(8080);

	//TODO: Correr en otro hilo
	server->start();

	delete server;

    return 0;
}
