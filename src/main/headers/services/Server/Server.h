#ifndef SRC_MAIN_MONGOOSESERVER_SERVER_H_
#define SRC_MAIN_MONGOOSESERVER_SERVER_H_

#include <extern/mongoose.h>
#include "../HTTP/HTTPRequestHandler.h"
#include <string>

using namespace std;

class Server {
private:
	/* Mongoose structs */
	struct mg_mgr eventManager; //Gestor de eventos que lleva a cabo todas las conexiones activas

	struct mg_connection* mongooseConnection; //Listener de las conexiones.

	//TODO: Acceder a la documentacion para sacarle provecho a este attr
	struct mg_bind_opts bindOptions; //Opciones personales para la conexion (mongoose no lo utiliza. Solo lo transporta)

	string documentRoot;

	string port;

	HTTPRequestHandler* HTTPHandler;

	void settingUpConnection();

	static void eventHandler(struct mg_connection* connection, int eventCode, void* eventData); //Handler propio para manipular los eventos de los request

public:
	Server(int port);

	void start();

	static void stop(int signal = 0);

	virtual ~Server();
};

#endif /* SRC_MAIN_MONGOOSESERVER_SERVER_H_ */
