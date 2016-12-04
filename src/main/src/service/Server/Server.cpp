#include <services/Server/Server.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPResponse.h>
#include <services/Logger/Logger.h>
#include <exception/AppServerException.h>
#include <iostream>

Server::Server(int connectionPort) {
	mg_mgr_init(&eventManager, NULL);

	running = false;
	port = to_string(connectionPort);

	bindOptions.user_data = (void*)this;
	mongooseConnection = mg_bind_opt(&eventManager, port.c_str(), this->eventHandler, bindOptions);

	if (mongooseConnection == NULL){
		Log("Failed to create Server in port: " + port + " [check that it is not running]", ERROR );
		throw AppServerException( "Failed to create Server in port: " + port + " [check that it is not running]" );
	} else {
		settingUpConnection();
	}
}

void Server::start(){
	running = true;
	Log("Server start at port: " + port + " [close it with Ctrl-C SIGINT or type \"exit\"]");

	while (running) {
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
			delete theRequest;
			if (mensaje == NULL){
				map<string,string> emptyHeaders;
				mensaje = new HTTPResponse("500","ERROR","",emptyHeaders);
			}
			mg_printf(connection, "%s",mensaje->toString().c_str());
			delete mensaje;
		} else {
			struct mg_serve_http_opts opts = { .document_root = (thisServer->documentRoot).c_str() };
			mg_serve_http(connection, (struct http_message *)eventData, opts);
		}

		connection->flags |= MG_F_SEND_AND_CLOSE;

	}
}

void Server::stop(){
	if(!running) return;
	running = false;
	Log("Server close");
}

string Server::getStats() {
	string message = (running) ? "OK. Server Running | " : "OK. ";
	message += "Number of processed request: " + to_string(HTTPHandler->getCount());
	return message;
}

Server::~Server() {
	if (running) this->stop();
	delete HTTPHandler;
	mg_mgr_free(&eventManager);
}

