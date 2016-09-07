#include "HTTPEndPoints.h"
#include "Server.h"

HTTPEndPoints::HTTPEndPoints() {
	/* Setup. Handler Mongoose -> Handler Propio */

	HelloWorldJsonHandler* helloWorld = new HelloWorldJsonHandler();
	HTTPHandlers["helloworld"] = (Handler*)helloWorld;

}

void HTTPEndPoints::helloWorld(struct mg_connection* connection, int eventCode, void* eventData){

	Server* theServer = (Server*)connection->user_data;
	Handler* theHandler = theServer->getHandler("helloworld");
	char* body = theHandler->handle();

	mg_printf(connection, "%s" ,body);

	connection->flags |= MG_F_SEND_AND_CLOSE;
}

Handler* HTTPEndPoints::getEndPoint(string endpoint){
	return HTTPHandlers[endpoint];
}

HTTPEndPoints::~HTTPEndPoints() {
	Log("Goodbye");
}
