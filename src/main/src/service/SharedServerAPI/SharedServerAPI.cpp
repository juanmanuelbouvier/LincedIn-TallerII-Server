#include <services/SharedServerAPI/SharedServerAPI.h>

#include <string>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <settings/SettingManager.h>

using namespace std;

SharedServerAPI* SharedServerAPI::instaceAPI = NULL;


SharedServerAPI::SharedServerAPI() {
	client = new ServerClient();
	sharedURL = SettingManager::getInstance()->getSharedServerURL();
	if (!client->connectToUrl(sharedURL)) {
		delete client;
	}

}

SharedServerAPI* SharedServerAPI::getInstance(){
	if (!instaceAPI) {
		instaceAPI = new SharedServerAPI();
	}
	return instaceAPI;
}

void SharedServerAPI::deleteInstance(){
	delete instaceAPI;
	instaceAPI = NULL;
}


HTTPResponse* SharedServerAPI::getSkills(){
	if (!client->connectToUrl(sharedURL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().GET()->setUri("/skills");
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);


}


SharedServerAPI::~SharedServerAPI() {
	delete client;
}

