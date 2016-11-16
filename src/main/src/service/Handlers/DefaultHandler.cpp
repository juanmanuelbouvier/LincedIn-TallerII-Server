#include "../../../headers/services/Handlers/DefaultHandler.h"
#include "../../../headers/services/HTTP/Message/HTTPMessageBuilder.h"

#include <string>

using namespace std;

HTTPResponse* DefaultHandler::handle(HTTPRequest* http_request){
	string mensaje = "LincedIn App Server | 2016";
	mensaje += "\n"
			"Request:\n"
			"\n" + http_request->toString();

	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-Type","text/plain");
	builder = (ResponseBuilder*)builder->setBody(mensaje);
	return builder->build();
}

