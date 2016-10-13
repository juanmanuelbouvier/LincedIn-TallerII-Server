#include <services/SharedServerAPI/SharedServerAPI.h>

#include <string>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>

using namespace std;

#define SHARED_SERVER_LOCAL_URL "localhost:8080"
#define SHARED_SERVER_HEROKU_URL "lincedin.herokuapp.com:80"

SharedServerAPI* SharedServerAPI::instaceAPI = NULL;


SharedServerAPI::SharedServerAPI() {
	client = new ServerClient();
	if (!client->connectToUrl(SHARED_SERVER_HEROKU_URL)) {
		delete client;
	}

}

SharedServerAPI* SharedServerAPI::getInstance(){
	if (!instaceAPI) {
		instaceAPI = new SharedServerAPI();
	}
	return instaceAPI;
}


HTTPResponse* SharedServerAPI::getSkills(){
	if (!client->connectToUrl(SHARED_SERVER_LOCAL_URL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().GET()->setUri("/skills");
	builder = (RequestBuilder*)builder->appendHeader("Host",string(SHARED_SERVER_LOCAL_URL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);


}


SharedServerAPI::~SharedServerAPI() {
	delete client;
	if(instaceAPI){
		instaceAPI = NULL;
	}
}

