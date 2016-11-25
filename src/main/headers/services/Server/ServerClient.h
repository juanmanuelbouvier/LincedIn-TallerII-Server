#ifndef SRC_MAIN_SERVICE_MONGOOSESERVER_SERVERCLIENT_H_
#define SRC_MAIN_SERVICE_MONGOOSESERVER_SERVERCLIENT_H_

#include <extern/mongoose.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPResponse.h>
#include <string>

using namespace std;

class ServerClient {
private:
	struct mg_mgr eventClientManager;
	struct mg_connection* mongooseClientConnection; //Listener de las conexiones.
	bool sendingRequest;
	string url;

	HTTPResponse* response;

	void handleHTTPReply(void* data);

	static void eventHandler(mg_connection* connection,int event_code,void* data);

public:

	bool connectToUrl(string url);

	HTTPResponse* sendRequest(HTTPRequest* request);

	ServerClient();
	virtual ~ServerClient();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_SERVERCLIENT_H_ */
