/*
 * DefaultHandler.cpp
 *
 *  Created on: 8 sep. 2016
 *      Author: tomi
 */

#include "DefaultHandler.h"

DefaultHandler::DefaultHandler() {

}

HTTPResponse* DefaultHandler::handle(HTTPRequest* http_request){
	string mensaje = "LincedIn App Server | 2016";


	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-Type","text/html; charset=utf-8");
	builder = (ResponseBuilder*)builder->setBody(mensaje);
	return builder->build();
}

DefaultHandler::~DefaultHandler() {
	// TODO Auto-generated destructor stub
}

