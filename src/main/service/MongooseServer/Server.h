/*
 * Server.h
 *
 *  Created on: 2 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_MONGOOSESERVER_SERVER_H_
#define SRC_MAIN_MONGOOSESERVER_SERVER_H_

#include "mongoose/mongoose.h"
#include "../Logger/Logger.h"
#include "HTTPEndPoints.h"
#include <iostream>

using namespace std;

class Server {
private:
	/* Mongoose structs */
	struct mg_mgr eventManager; //Gestor de eventos que lleva a cabo todas las conexiones activas

	struct mg_connection* mongooseConnection; //Listener de las conexiones.

	//TODO: Acceder a la documentacion para sacarle provecho a este attr
	struct mg_bind_opts bindOptions; //Opciones personales para la conexion (mongoose no lo utiliza. Solo lo transporta)

	string port;

	HTTPEndPoints* endPoints;

	void settingUpConnection();
	static void stop(int signal = 0);
	static void eventHandler(struct mg_connection* connection, int eventCode, void* eventData); //Handler propio para manipular los eventos de los request

public:
	Server(int port);

	void start();

	void setHTTPHandler(string uri, mg_event_handler_t handler);

	Handler* getHandler(string uriName);

	virtual ~Server();
};

#endif /* SRC_MAIN_MONGOOSESERVER_SERVER_H_ */
