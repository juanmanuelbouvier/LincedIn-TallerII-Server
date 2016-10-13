#ifndef SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPMESSAGEBUILDER_H_
#define SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPMESSAGEBUILDER_H_

#include <iostream>
#include <map>
#include "HTTPRequest.h"
#include "HTTPResponse.h"

using namespace std;

class MessageBuilder {
protected:
	map<string,string> headers;
	string body;


public:
	MessageBuilder();

	MessageBuilder* setBody(string body);
	MessageBuilder* addHeader(map<string,string> theHeathers);
	MessageBuilder* appendHeader(string key, string value);
	MessageBuilder* joinHeader(map<string,string> otherMap);

	virtual ~MessageBuilder();
};

class RequestBuilder : public MessageBuilder {
private:
	string uri;
	string method;
	string query;


public:
	RequestBuilder();

	RequestBuilder* GET();
	RequestBuilder* PUT();
	RequestBuilder* DELETE();
	RequestBuilder* POST();
	RequestBuilder* setMethod(string method);
	RequestBuilder* setUri(string uri);
	RequestBuilder* setQuery(string theQuery);

	HTTPRequest* build();

	virtual ~RequestBuilder();
};

class ResponseBuilder : public MessageBuilder {
private:
	string code;
	string phrase;

public:
	ResponseBuilder();

	ResponseBuilder* setCode(int code);
	ResponseBuilder* setCodeAndPhrase(int code,string thePhrase);

	HTTPResponse* build();

	virtual ~ResponseBuilder();
};

#endif /* SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPMESSAGEBUILDER_H_ */
