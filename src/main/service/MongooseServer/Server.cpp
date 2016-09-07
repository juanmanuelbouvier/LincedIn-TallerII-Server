#include "Server.h"
#include <map>

volatile static bool SERVER_RUNNING;

Server::Server(int connectionPort) {
	mg_mgr_init(&eventManager, NULL);

	SERVER_RUNNING = false;
	port = to_string(connectionPort);

	bindOptions.user_data = (void*)this;

	mongooseConnection = mg_bind_opt(&eventManager, port.c_str(), this->eventHandler, bindOptions);
	if (!mongooseConnection){
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

	endPoints = new HTTPEndPoints();
	Log("set up endpoint '/helloworld'");
	this->setHTTPHandler("/helloworld",endPoints->helloWorld);
}

void Server::eventHandler(struct mg_connection* connection, int eventCode, void* eventData){
	//Por el momento solo manejamos request del tipo http.

	//TODO: Si trabajamos solo con HTTP hay que ver este link [https://docs.cesanta.com/mongoose/master/#/c-api/http_server.h/mg_register_http_endpoint.md/]
	if (eventCode == MG_EV_HTTP_REQUEST){
		struct http_message* msg = (struct http_message *)eventData;

		string verb = string(msg->method.p,msg->method.len);
		string uri = string(msg->uri.p,msg->uri.len);
		string query = string(msg->query_string.p,msg->query_string.len);

		string mensaje = "<h1>Linced In App Server</h1>\n<h2><b>METODO: </b>"+ verb +"</h2>\n<h2><b>URI: </b>"+ uri +"</h2>\n<h2><b>QUERY: </b>"+ query +"</h2>";

		mg_send_head(connection, 200, mensaje.length(), "HTTP/1.1");
		mg_printf(connection, "%s",mensaje.c_str());

		connection->flags |= MG_F_SEND_AND_CLOSE;

	}
}

void Server::setHTTPHandler(string uri, mg_event_handler_t handlerFuncion){
	mg_register_http_endpoint(mongooseConnection, uri.c_str(),handlerFuncion);
}

void Server::stop(int signal){
	if(!SERVER_RUNNING) return;
	SERVER_RUNNING = false;
	Log("Server close");
}

Handler* Server::getHandler(string uriName){
	return endPoints->getEndPoint(uriName);
}

Server::~Server() {
	if (SERVER_RUNNING) this->stop();
	mg_mgr_free(&eventManager);
}

