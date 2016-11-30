#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <services/Logger/Logger.h>

#define MAX_CICLES 10
#define WAIT_REPLY 2

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
#include <utils/DateUtils.h>
HTTPResponse* ServerClient::sendRequest(HTTPRequest* request) {
	mg_printf(mongooseClientConnection, "%s", request->toString().c_str());
	sendingRequest = true;
	waitHTTPReply = false;
	if (response != NULL) {
		delete response;
		response = NULL;
	}

	int init = DateUtils::timestamp();

	cicles = 0;
	while (sendingRequest) {
		if (cicles > MAX_CICLES) {
			LOG(url + " does not respond. Returning TIMEOUT response",WARNING);
			response = ResponseBuilder::createErrorResponse(408,"TIMEOUT");
			sendingRequest = false;
			waitHTTPReply = false;
			break;
		}
		mg_mgr_poll(&eventClientManager, 1000);
		cicles++;
	}
	int fin = DateUtils::timestamp() - init;
	if (fin > 1) {
		printf("TIME: %d\nRequest\n%s\n====\nResponse:\n%s\n",fin,request->toString().c_str(),response->toString().c_str());
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
