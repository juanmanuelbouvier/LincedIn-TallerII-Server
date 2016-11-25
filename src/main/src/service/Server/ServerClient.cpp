#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <services/Logger/Logger.h>

#define MAX_CICLES 200

using namespace std;

ServerClient::ServerClient() {
	mg_mgr_init(&eventClientManager, NULL);
	sendingRequest = false;
	mongooseClientConnection = NULL;
	response = NULL;
	url = "";

}

HTTPResponse* ServerClient::sendRequest(HTTPRequest* request) {
	mg_printf(mongooseClientConnection, "%s", request->toString().c_str());
	sendingRequest = true;

	int cicles = 0;
	while (sendingRequest) {
		if (cicles > MAX_CICLES) {
			string host = request->getFromHeader("Host");
			LOG(host + " does not respond. Returning TIMEOUT response",WARNING);
			response = ResponseBuilder::createErrorResponse(408,"TIMEOUT");
			sendingRequest = false;
			break;
		}
		mg_mgr_poll(&eventClientManager, 1000);
		cicles++;
		if (response){
			cout << response->toString() + " in cicle " +  to_string(cicles) << endl;
			time_t now = time(0);
			tm *ltm = localtime(&now);
			cout << "Time: "<< ltm->tm_hour << ":";
			cout <<  ltm->tm_min << ":";
			cout << ltm->tm_sec << endl;
		}

	}
	cout << "cicles " + to_string(cicles) << endl;
	return response;
}

void ServerClient::handleHTTPReply(void* data){
	struct http_message* message = (struct http_message *)data;
	response = new HTTPResponse(message);
	sendingRequest = false;

}


void ServerClient::eventHandler(mg_connection* connection, int event_code, void* data) {
	cout << "evento " +  to_string(event_code) << endl;
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
		mg_set_protocol_http_websocket(mongooseClientConnection);
		this->url = url;
	}
	return (mongooseClientConnection != NULL);
}

ServerClient::~ServerClient() {
	mg_mgr_free(&eventClientManager);
	mongooseClientConnection = NULL;
}
