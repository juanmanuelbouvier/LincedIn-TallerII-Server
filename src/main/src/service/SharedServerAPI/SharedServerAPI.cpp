#include <services/SharedServerAPI/SharedServerAPI.h>

#include <string>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <settings/SettingManager.h>
#include <utils/JSONUtils.h>

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

HTTPResponse* SharedServerAPI::doPut(string uri, string body){
	if (!client->connectToUrl(sharedURL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().PUT()->setUri(uri)->setBody(body);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);
}

Json::Value SharedServerAPI::getSkills(){
	HTTPResponse* response = doGet("/skills");
	Json::Value res = JSONUtils::stringToJSON(response->getBody());
	return res["skills"];
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
	Json::Value error;
	error["error"] = "skill inexistente.";
	return error;
}

Json::Value SharedServerAPI::setSkill(string name,string description, string category){
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\" }";
	HTTPResponse* response = doPost("/skills/categories/"+category,body);

	Json::Value res;

	if (response->getCode() == 200){
		res["ok"] = name;
	}
	else {
		res["error"] = JSONUtils::stringToJSON(response->getBody())["message"];
	}

	return res;
}

Json::Value SharedServerAPI::updateSkill(string name,string description, string category){
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\", \"category\":\""+category +"\" }";
	HTTPResponse* response = doPut("/skills/categories/"+category+"/"+name , body);

	Json::Value res;

	if (response->getCode() == 200){
		res["ok"] = name;
	}
	else {
		res["error"] = JSONUtils::stringToJSON(response->getBody())["message"];
	}

	return res;
}

SharedServerAPI::~SharedServerAPI() {
	delete client;
}

