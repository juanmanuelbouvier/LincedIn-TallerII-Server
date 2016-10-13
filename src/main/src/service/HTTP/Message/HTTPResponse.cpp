#include <services/HTTP/Message/HTTPResponse.h>

#define HTTP_VERSION "HTTP/1.1"
const string HTTP_CRLF = "\r\n";

HTTPResponse::HTTPResponse(struct http_message* msg){
	httpRawMessage = string(msg->message.p, msg->message.len);

	code 	= to_string(msg->resp_code);
	phrase 	= string(msg->resp_status_msg.p,msg->resp_status_msg.len);
	body	= string(msg->body.p,msg->body.len);

	for (int i = 0; i < MG_MAX_HTTP_HEADERS; i++){
		headers[ string(msg->header_names[i].p,msg->header_names[i].len) ] = string(msg->header_values[i].p,msg->header_values[i].len);
	}

}

HTTPResponse::HTTPResponse(string _code, string _phrase, string _body, map<string,string> _headers){

	code 	= _code;
	phrase 	= _phrase;
	body	= _body;
	headers = _headers;

	generateRawMessage();

}

void HTTPResponse::generateRawMessage(){
	//Status-line
	httpRawMessage = HTTP_VERSION;
	httpRawMessage += " " + code + " " + phrase + HTTP_CRLF;

	//Zero or more headers
	for (map<string,string>::iterator it = headers.begin(); it != headers.end(); ++it) {
		httpRawMessage += it->first + ":" + it->second + HTTP_CRLF;
	}
	if (body.size() > 0) {
		httpRawMessage += "Content-Length:" + body.length() + HTTP_CRLF;
		//An Empty line indicating end of headers
		httpRawMessage += HTTP_CRLF;

		//Message body
		httpRawMessage += body + HTTP_CRLF;
	}
	httpRawMessage += HTTP_CRLF;
}

string HTTPResponse::getStringCode(){
	return code;
}

int HTTPResponse::getCode(){
	return stoi( code );
}

string HTTPResponse::getPhrase(){
	return phrase;
}

string HTTPResponse::getFromHeader(string key){
	return headers[key];
}

string HTTPResponse::getBody(){
	return body;
}

string HTTPResponse::toString(){
	return httpRawMessage;
}

HTTPResponse::~HTTPResponse(){

}
