#include "SharedServerHandler.h"
#include "../Logger/Logger.h"

SharedServerHandler::SharedServerHandler() {
}

HTTPResponse* SharedServerHandler::handle(HTTPRequest* http_request){
	
	return SharedServerAPI::getInstance()->getSkills();
}

SharedServerHandler::~SharedServerHandler(){

}
