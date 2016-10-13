#ifndef SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPRESPONSE_H_
#define SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPRESPONSE_H_

#include <string>
#include <map>
#include <extern/mongoose.h>

using namespace std;

class HTTPResponse {
	map<string,string> headers;

	string httpRawMessage;

	string code;
	string phrase;
	string body;

	void generateRawMessage();


public:
	HTTPResponse(struct http_message* msg);
	HTTPResponse(string code, string phrase, string body,map<string,string> headers);

	string getStringCode();
	int getCode();
	string getPhrase();
	string getFromHeader(string key);
	string getBody();

	string toString();

	virtual ~HTTPResponse();
};

#endif /* SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPRESPONSE_H_ */
