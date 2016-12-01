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
	 * Create server in port.
	 * @param Port of the listening requests
	 * @note Throw exception if the port is in use or not have permission
	 */
	Server(int port);

	/**
	 * Start to listen requests in assigned port
	 */
	void start();

	void stop();

	/**
	 * Get the summary of the HTTP Requests
	 * @return Pretty string with summary
	 */
	string getStats();

	virtual ~Server();
};

#endif /* SRC_MAIN_MONGOOSESERVER_SERVER_H_ */
