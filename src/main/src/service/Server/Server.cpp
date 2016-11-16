#include <services/Server/Server.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPResponse.h>
#include <services/Logger/Logger.h>
#include <exception/AppServerException.h>

volatile static bool SERVER_RUNNING;

Server::Server(int connectionPort) {
	mg_mgr_init(&eventManager, NULL);

	SERVER_RUNNING = false;
	port = to_string(connectionPort);

	bindOptions.user_data = (void*)this;
	mongooseConnection = mg_bind_opt(&eventManager, port.c_str(), this->eventHandler, bindOptions);

	if (mongooseConnection == NULL){
		throw AppServerException( Log("Failed to create Server in port: " + port + " [check that it is not running]", ERROR ) );
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

	HTTPHandler = new HTTPRequestHandler();

}

void Server::eventHandler(struct mg_connection* connection, int eventCode, void* eventData){
	if (eventCode == MG_EV_HTTP_REQUEST){
		Server* thisServer = (Server*)connection->user_data;

		HTTPRequest* theRequest = new HTTPRequest((struct http_message *)eventData);

		if (thisServer->HTTPHandler->isHandledRequest(theRequest)){
			HTTPResponse* mensaje = thisServer->HTTPHandler->handle(theRequest);
			if (!mensaje){
				map<string,string> emptyHeaders;
				mensaje = new HTTPResponse("400","ERROR","",emptyHeaders);
			}
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

