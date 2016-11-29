#ifndef SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPREQUEST_H_
#define SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPREQUEST_H_

#include <extern/mongoose.h>
#include <string>
#include <map>

using namespace std;

/**
 * Wrapper of a raw request.
 */
class HTTPRequest {
private:
	map<string,string> headers;

	//Raw message of the request
	string httpMessage;

	string method;
	string uri;
	string query;
	string body;

	void generateRawMessage();

public:
	/**
	 * Create rquest with default values
	 */
	HTTPRequest();

	/**
	 * Create request from a mongoose message
	 */
	HTTPRequest(struct http_message* msg);

	/**
	 * Create response from specific parameters
	 */
	HTTPRequest(string method, string uri, string query, string body, map<string,string> headers);

	string getMethod();
	string getURI();
	string getQuery();
	string getBody();
	string getFromHeader(string key);

	bool isGET();
	bool isPOST();
	bool isDELETE();
	bool isPATCH();
	bool isPUT();

	string toString();

	virtual ~HTTPRequest();
};

#endif /* SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPREQUEST_H_ */
