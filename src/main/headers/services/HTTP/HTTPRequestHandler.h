#ifndef SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_
#define SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_


#include <services/Handlers/Handler.h>
#include "Message/HTTPRequest.h"
#include "Message/HTTPResponse.h"

#include <map>
#include <vector>

using namespace std;

/**
 * HTTPRequestHandler is a class who Handle all handlers.
 * When the object recive and request to handler. Call a defined Handler to the uri in the request
 * The uris can contains variables like NODEJS Express (ej. /user/:user_name)
 */
class HTTPRequestHandler {

private:
	map<string,Handler*> HTTPEndPointsHandlers;
	vector<string> workingPaths;
	int count;
	string matchPath( string uri );
	void registerPath( string path );
	void accessLog(HTTPRequest* http_request);

public:
	HTTPRequestHandler();

	/**
	 * Handle a request with internal and designed handler
	 * @param Request to be handled
	 * @return A Response who was received from the Handler
	 */
	HTTPResponse* handle(HTTPRequest* http_request);

	/**
	 * Check if exist a handler who can handle the request
	 * @note The parameter to check if the uri in the request
	 */
	bool isHandledRequest(HTTPRequest* http_request);

	/**
	 * Add Handler for specific uri path.
	 * @param uri_path
	 * @param Handler
	 * @return True if could be added
	 */
	bool addHandler(string uri_path, Handler* handler);

	/**
	 * Get Number of request they were processed
	 * @return number of handled request
	 */
	int getCount() { return count; };

	virtual ~HTTPRequestHandler();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUESTHANDLER_H_ */
