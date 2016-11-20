#include <services/HTTP/Message/HTTPRequest.h>
#include <utils/StringUtils.h>

#define HTTP_VERSION "HTTP/1.1"
const string HTTP_CRLF = "\r\n";

HTTPRequest::HTTPRequest(){

	method 	= "GET";
	uri 	= "/";
	query 	= "";
	body	= "";

	generateRawMessage();
};

HTTPRequest::HTTPRequest(struct http_message* msg) {
	httpMessage = string(msg->message.p,msg->message.len);

	method 	= string(msg->method.p,msg->method.len);
	uri 	= string(msg->uri.p,msg->uri.len);
	query 	= string(msg->query_string.p,msg->query_string.len);
	body	= string(msg->body.p, msg->body.len);

	for (int i = 0; i < MG_MAX_HTTP_HEADERS; i++) {
		struct mg_str name = msg->header_names[i];
		struct mg_str value = msg->header_values[i];
		string nameHeader  = string(name.p,name.len);
		string valueHeader = string(value.p,value.len);
		headers[nameHeader] = valueHeader;
	}

}

HTTPRequest::HTTPRequest(string _method, string _uri, string _query, string _body, map<string,string> _headers){

	method 	= _method;
	uri		= _uri;
	query	= _query;
	body	= _body;
	headers	= _headers;

	generateRawMessage();
}

void HTTPRequest::generateRawMessage(){
	//A Request-line
	string queryWithSimbol = (query.empty()) ? "" : "?" + query;
	httpMessage = method + " " + uri + queryWithSimbol + " " + HTTP_VERSION;
	httpMessage += HTTP_CRLF;

	//Zero or more header
	for (map<string,string>::iterator it = headers.begin(); it != headers.end(); ++it) {
		httpMessage += it->first + ": " + it->second + HTTP_CRLF;
	}

	//Optionally a message-body
	if (body.length() > 0) {
		httpMessage += "Content-Length:" + to_string(body.length()) + HTTP_CRLF;
		//An empty line (i.e., a line with nothing preceding the CRLF) indicating the end of the header fields
		httpMessage += HTTP_CRLF;
		httpMessage +=  body;
	}
	httpMessage += HTTP_CRLF;
}

string HTTPRequest::getMethod(){
	return method;
}

bool HTTPRequest::isGET(){
	return method == "GET";
}

bool HTTPRequest::isPOST(){
	return method == "POST";
}

bool HTTPRequest::isDELETE() {
	return method == "DELETE";
}

bool HTTPRequest::isPATCH() {
	return method == "PATCH";
}

bool HTTPRequest::isPUT() {
	return method == "PUT";
}

string HTTPRequest::getURI(){
	return StringUtils::unescapeString(uri);
}
string HTTPRequest::getQuery(){
	return query;
}
string HTTPRequest::getBody(){
	return body;
}

string HTTPRequest::getFromHeader(string key){
	if ( headers.find(key) != headers.end() ) {
		return headers[key];
	}
	return "";
}

string HTTPRequest::toString(){
	return httpMessage;
}

HTTPRequest::~HTTPRequest(){

}
