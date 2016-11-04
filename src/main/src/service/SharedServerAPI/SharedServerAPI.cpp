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

HTTPResponse* SharedServerAPI::doPost( string uri, string body ){
	if (!client->connectToUrl(sharedURL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().POST()->setUri(uri)->setBody(body);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);
}

HTTPResponse* SharedServerAPI::getSkills(){
	return doGet("/skills");
}

Json::Value SharedServerAPI::getSkill(string name){
	HTTPResponse* response = doGet("/skills");
	Json::Value body = response->getBody();
	Json::Value skills = body["skills"];

	for( Json::ValueIterator itr = skills.begin() ; itr != skills.end() ; itr++ ) {
		Json::Value skill = itr.key();
		if (skill["name"].toStyledString() == name) {
			return skill;
		}
	}
	Json::Value val;
	return val;
}

HTTPResponse* SharedServerAPI::setSkill(string name,string description, string category){
	string body = "{ \"description\":"+ description +", \"name\":"+ name +" }";
	return doPost("/skills/categories/"+category,body);

}

SharedServerAPI::~SharedServerAPI() {
	delete client;
}

