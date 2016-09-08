/*
 * HTTPRequest.cpp
 *
 *  Created on: 8 sep. 2016
 *      Author: tomi
 */

#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(struct http_message* msg) {
	httpMessage = msg;

	method 	= string(msg->method.p,msg->method.len);
	uri 	= string(msg->uri.p,msg->uri.len);
	query 	= string(msg->query_string.p,msg->query_string.len);
	body	= string(msg->body.p, msg->body.len);

}

string HTTPRequest::getMethod(){
	return method;
}
string HTTPRequest::getURI(){
	return uri;
}
string HTTPRequest::getQuery(){
	return query;
}
string HTTPRequest::getBody(){
	return body;
}


HTTPRequest::~HTTPRequest() {
	delete httpMessage;
}

