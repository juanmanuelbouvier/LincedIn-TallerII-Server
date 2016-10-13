#ifndef SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPREQUEST_H_
#define SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPREQUEST_H_

#include <extern/mongoose.h>
#include <string>
#include <map>

using namespace std;


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
	HTTPRequest();
	HTTPRequest(struct http_message* msg);
	HTTPRequest(string method, string uri, string query, string body, map<string,string> headers);

	string getMethod();
	string getURI();
	string getQuery();
	string getBody();
	string getFromHeader(string key);

	string toString();

	virtual ~HTTPRequest();
};

#endif /* SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPREQUEST_H_ */
