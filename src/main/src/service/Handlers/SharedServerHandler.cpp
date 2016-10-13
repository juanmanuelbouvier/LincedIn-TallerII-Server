#include "services/Handlers/SharedServerHandler.h"
#include "services/SharedServerAPI/SharedServerAPI.h"


SharedServerHandler::SharedServerHandler() {
}

HTTPResponse* SharedServerHandler::handle(HTTPRequest* http_request){
	
	return SharedServerAPI::getInstance()->getSkills();
}

SharedServerHandler::~SharedServerHandler(){

}
