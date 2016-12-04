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

	void setDefault();

	static void eventHandler(mg_connection* connection,int event_code,void* data);
protected:
	int cicles;
public:
	/**
	 * Connect to url.
	 * @param url to connect.
	 * @return True if could connect.
	 */
	bool connectToUrl(string url);

	/**
	 * Send request to the client.
	 * @param Request to be sended
	 * @return Response of the server. If the time of response exceed MAX_CICLES. Return timeout response
	 */
	HTTPResponse* sendRequest(HTTPRequest* request);

	bool waitHTTPReply;
	ServerClient();
	virtual ~ServerClient();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_SERVERCLIENT_H_ */
