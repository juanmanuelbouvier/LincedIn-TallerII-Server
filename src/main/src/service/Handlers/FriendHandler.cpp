#include "FriendHandler.h"
#include <services/HTTP/Message/HTTPMessageBuilder.h>


HTTPResponse* FriendHandler::handle(HTTPRequest* http_request) {

	string body = "";
	int code = 200;

	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-type","application/json")->setBody(body);
	builder = (ResponseBuilder*)builder->setCode(code);
	return builder->build();

}
