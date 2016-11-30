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

	//Roots of file documents. The Server can listen on /file.ext and search these file in the "documentRoot"
	string documentRoot;

	string port;

	bool running;

	HTTPRequestHandler* HTTPHandler;

	//Set-up Mongoose setting and create Handlers
	void settingUpConnection();

	static void eventHandler(struct mg_connection* connection, int eventCode, void* eventData);

public:
	/**
	 * Create server in port. Throw exception if TODO (Si no puede)
	 * @param Port of the listening requests
	 */
	Server(int port);

	void start();

	void stop();

	virtual ~Server();
};

#endif /* SRC_MAIN_MONGOOSESERVER_SERVER_H_ */
