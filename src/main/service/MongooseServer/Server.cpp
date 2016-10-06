#include "Server.h"

volatile static bool SERVER_RUNNING;

Server::Server(int connectionPort) {
	mg_mgr_init(&eventManager, NULL);

	SERVER_RUNNING = false;
	port = to_string(connectionPort);

	bindOptions.user_data = (void*)this;
	mongooseConnection = mg_bind_opt(&eventManager, port.c_str(), this->eventHandler, bindOptions);

	if (mongooseConnection == NULL){
		//TODO: Lanzar Excepcion, no se puede continuar.
		Log("Failed to create Server in port: " + port + " [check that it is not running]", ERROR );
		return;
	} else {
		settingUpConnection();
	}
}

void Server::start(){
	SERVER_RUNNING = true;

	signal(SIGINT, this->stop);
	Log("Server start at port: " + port + " [close it with Ctrl-C SIGINT]");

	while (SERVER_RUNNING) {
    	mg_mgr_poll(&eventManager, 1000);
  	}
}

void Server::settingUpConnection(){
	mg_set_protocol_http_websocket(mongooseConnection);
	mg_enable_multithreading(mongooseConnection);

	documentRoot = "resources/";

	//TODO: Para que el server no sea tan responsable podria hacerse externamente y generarlo con un set o en el propio init.
	HTTPHandler = new HTTPRequestHandler();

}

void Server::eventHandler(struct mg_connection* connection, int eventCode, void* eventData){
	//Por el momento solo manejamos request del tipo http.

	//TODO: Si trabajamos solo con HTTP hay que ver este link [https://docs.cesanta.com/mongoose/master/#/c-api/http_server.h/mg_register_http_endpoint.md/]
	// REV: features/httendpoints implementa el TODO. No es util por como matchea el uri. Se implementa un algoritmo propio que resuelve los, mediante el URI, a que handler dirigirse.
	if (eventCode == MG_EV_HTTP_REQUEST){
		/*
		 * TODO:
		 * 	- Se recibe un request. Hay que transformar el request de Mongoose en un objeto propio.
		 * 	- Un handler (no importa), procesara el request.
		 * 	- El Handler generara un response que se enviara con mg_send_head y mg_printf
		 * */

		Server* thisServer = (Server*)connection->user_data;

		HTTPRequest* theRequest = new HTTPRequest((struct http_message *)eventData);

		if (thisServer->HTTPHandler->isHandledRequest(theRequest)){
			HTTPResponse* mensaje = thisServer->HTTPHandler->handle(theRequest);

			//TODO 2: El status code y los extra headers tienen que venir desde el handler
			//mg_send_head(connection, 200, mensaje.length(), "HTTP/1.1");
			mg_printf(connection, "%s",mensaje->toString().c_str());

		} else {
			struct mg_serve_http_opts opts = { .document_root = (thisServer->documentRoot).c_str() };
			mg_serve_http(connection, (struct http_message *)eventData, opts);
		}

		connection->flags |= MG_F_SEND_AND_CLOSE;

	}
}

void Server::stop(int signal){
	if(!SERVER_RUNNING) return;
	SERVER_RUNNING = false;
	Log("Server close");
}

Server::~Server() {
	if (SERVER_RUNNING) this->stop();
	delete HTTPHandler;
	mg_mgr_free(&eventManager);
}

