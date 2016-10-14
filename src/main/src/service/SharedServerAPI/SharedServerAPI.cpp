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

vector<string> SharedServerAPI::getsURL() {
	vector<string> urls = {
		"/job_positions/categories/:category",
		"/job_positions",
		"/skills",
		"/skills/categories/:category/:name",
		"/categories"
	};

	return urls;
}

HTTPResponse* SharedServerAPI::doGet( string uri ){
	if (!client->connectToUrl(sharedURL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().GET()->setUri(uri);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);
}

HTTPResponse* SharedServerAPI::getSkills(){
	return doGet("/skills");
}


SharedServerAPI::~SharedServerAPI() {
	delete client;
}

