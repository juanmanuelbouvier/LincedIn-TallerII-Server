#ifndef SRC_MAIN_MONGOOSESERVER_SERVER_H_
#define SRC_MAIN_MONGOOSESERVER_SERVER_H_

#include <extern/mongoose.h>
#include "../HTTP/HTTPRequestHandler.h"
#include <string>

using namespace std;

class Server {
private:
	/* Mongoose structs */
	//Event manager that performs all active connections
	struct mg_mgr eventManager;

	//Listener of the connectoons.
	struct mg_connection* mongooseConnection;

	//Personal options for the connections (Mongoose just carry it)
	struct mg_bind_opts bindOptions;

	string documentRoot;

	string port;

	HTTPRequestHandler* HTTPHandler;

	void settingUpConnection();

	static void eventHandler(struct mg_connection* connection, int eventCode, void* eventData);

public:
	Server(int port);

	void start();

	static void stop(int signal = 0);

	virtual ~Server();
};

#endif /* SRC_MAIN_MONGOOSESERVER_SERVER_H_ */
