/*
 * HTTPRequestHandler.cpp
 *
 *  Created on: 7 sep. 2016
 *      Author: tomi
 */

#include "HTTPRequestHandler.h"

HTTPRequestHandler::HTTPRequestHandler() {
	// Inicialize all Handlers.

	//TODO: Se tiene que resolver mediante regular expresion las uris con variables
	HTTPEndPointsHandlers["/helloworld"] = new HelloWorldJsonHandler();

	//Defaults
	HTTPEndPointsHandlers["/"] = new DefaultHandler();
	HTTPEndPointsHandlers["/index"] = HTTPEndPointsHandlers["/"];

	HTTPEndPointsHandlers["/skills"] = new SharedServerHandler();

}

HTTPResponse* HTTPRequestHandler::handle(HTTPRequest* http_request){
	//TODO: Si no existe URI devuelve NOT FOUND
	string uri = http_request->getURI();

	//Se supone que por decision del server esto ya tiene que venir verificado
	if ( !isHandledRequest(http_request) ){
		Log("No Handler for endpoint = `" + uri + "` go to DefaultHandler",INFO);
		return HTTPEndPointsHandlers["/"]->handle(http_request);
	}
	return HTTPEndPointsHandlers[uri]->handle(http_request);
}

bool HTTPRequestHandler::isHandledRequest(HTTPRequest* http_request) {
	string uri = http_request->getURI();
	if (uri.empty() || uri == "/"){
		return true;
	}

	if (HTTPEndPointsHandlers.find(uri) != HTTPEndPointsHandlers.end()){
		return true;
	}
	return false;
}

HTTPRequestHandler::~HTTPRequestHandler() {
	HTTPEndPointsHandlers.clear();
}

