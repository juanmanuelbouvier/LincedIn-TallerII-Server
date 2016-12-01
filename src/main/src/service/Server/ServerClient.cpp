#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <services/Logger/Logger.h>

#define MAX_CICLES 50
#define WAIT_REPLY 25

using namespace std;

ServerClient::ServerClient() {
	mg_mgr_init(&eventClientManager, NULL);
	sendingRequest = false;
	mongooseClientConnection = NULL;
	response = NULL;
	url = "";
	cicles = 0;
	waitHTTPReply = false;

}

void ServerClient::setDefault() {
	waitHTTPReply = false;
	if (response != NULL) {
		response = NULL;
	}
	cicles = 0;
}

HTTPResponse* ServerClient::sendRequest(HTTPRequest* request) {
	setDefault();

	mg_printf(mongooseClientConnection, "%s", request->toString().c_str());

	sendingRequest = true;
	while (sendingRequest) {
		if (cicles > MAX_CICLES) {
			LOG(url + " does not respond. Returning TIMEOUT response",WARNING);
			printf("TIMEOUT\n");
			response = ResponseBuilder::createErrorResponse(408,"TIMEOUT");
			sendingRequest = false;
			waitHTTPReply = false;
			break;
		}
		mg_mgr_poll(&eventClientManager, 1000);
		cicles++;
	}
	return response;
}

void ServerClient::handleHTTPReply(void* data){
	struct http_message* message = (struct http_message *)data;
	response = new HTTPResponse(message);
	sendingRequest = false;
}


void ServerClient::eventHandler(mg_connection* connection, int event_code, void* data) {
	ServerClient* clientConnection = (ServerClient*) connection->user_data;
	if (event_code == MG_EV_POLL && clientConnection->cicles >= WAIT_REPLY && clientConnection->waitHTTPReply) {
		connection->flags |= MG_F_CLOSE_IMMEDIATELY;
	}
	if (event_code == MG_EV_HTTP_REPLY) {
		clientConnection->handleHTTPReply(data);
		connection->flags |= MG_F_CLOSE_IMMEDIATELY;
	}
	if (event_code == MG_EV_RECV) {
		//HOTFIX: Mongoose <---> NodeJS Express
		clientConnection->waitHTTPReply = true;
	}
}

bool ServerClient::connectToUrl(string url){
	mongooseClientConnection = mg_connect_http(&eventClientManager, this->eventHandler, url.c_str(),NULL,NULL);
	if (mongooseClientConnection) {
		mongooseClientConnection->user_data = this;
		mg_set_protocol_http_websocket(mongooseClientConnection);
		this->url = url;
	}
	return (mongooseClientConnection != NULL);
}

ServerClient::~ServerClient() {
	mg_mgr_free(&eventClientManager);
	mongooseClientConnection = NULL;
}
