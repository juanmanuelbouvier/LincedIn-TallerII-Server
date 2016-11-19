#include <services/Server/ServerClient.h>

using namespace std;

ServerClient::ServerClient() {
	mg_mgr_init(&eventClientManager, NULL);
	sendingRequest = false;
	mongooseClientConnection = NULL;
	response = NULL;

}

HTTPResponse* ServerClient::sendRequest(HTTPRequest* request) {
	mg_printf(mongooseClientConnection, "%s", request->toString().c_str());
	sendingRequest = true;
	while (sendingRequest) {
		mg_mgr_poll(&eventClientManager, 1000);
	}
	return response;
}

void ServerClient::handleHTTPReply(void* data){
	struct http_message* message = (struct http_message *)data;
	response = new HTTPResponse(message);
	sendingRequest = false;

}


void ServerClient::eventHandler(mg_connection* connection, int event_code, void* data) {
	if (event_code == MG_EV_HTTP_REPLY) {
		ServerClient* clientConnection = (ServerClient*) connection->user_data;
		clientConnection->handleHTTPReply(data);
		connection->flags |= MG_F_CLOSE_IMMEDIATELY;
	}
}

bool ServerClient::connectToUrl(string url){
	mongooseClientConnection = mg_connect_http(&eventClientManager, this->eventHandler, url.c_str(),NULL,NULL);
	if (mongooseClientConnection) {
		mongooseClientConnection->user_data = this;
		mg_set_protocol_http_websocket(mongooseClientConnection);;
	}
	return (mongooseClientConnection != NULL);
}

ServerClient::~ServerClient() {
	mg_mgr_free(&eventClientManager);
	mongooseClientConnection = NULL;
}
