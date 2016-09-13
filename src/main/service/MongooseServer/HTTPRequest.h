/*
 * HTTPRequest.h
 *
 *  Created on: 8 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUEST_H_
#define SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUEST_H_

#include "mongoose/mongoose.h"
#include <iostream>

using namespace std;


class HTTPRequest {
private:
	struct http_message* httpMessage;

	string method;
	string uri;
	string query;
	string body;

public:
	HTTPRequest(struct http_message* msg);

	string getMethod();
	string getURI();
	string getQuery();
	string getBody();

	virtual ~HTTPRequest();
};

#endif /* SRC_MAIN_SERVICE_MONGOOSESERVER_HTTPREQUEST_H_ */
