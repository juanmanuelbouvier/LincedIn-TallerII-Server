#ifndef SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPMESSAGEBUILDER_H_
#define SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPMESSAGEBUILDER_H_

#include <iostream>
#include <map>
#include <extern/json.h>
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
	RequestBuilder* setBody(string theBody);

	HTTPRequest* build();


	virtual ~RequestBuilder();
};

class ResponseBuilder : public MessageBuilder {
private:
	string code;
	string phrase;
	static Json::Value ResponseBuilder::createErrorJSON(string message,int internal_code);

public:
	ResponseBuilder();

	ResponseBuilder* setCode(string code);
	ResponseBuilder* setCodeAndPhrase(string code,string thePhrase);

	HTTPResponse* build();

	static HTTPResponse* createJsonResponse(int code, Json::Value body);
	static HTTPResponse* createJsonResponse(int code, string body);
	static HTTPResponse* createOKResponse(int code, string message);
	static HTTPResponse* createErrorResponse(int code, string error);
	static HTTPResponse* createErrorResponse(int code, string error,int internal_code);

	virtual ~ResponseBuilder();
};

#endif /* SRC_MAIN_SERVICE_HTTP_MESSAGE_HTTPMESSAGEBUILDER_H_ */
