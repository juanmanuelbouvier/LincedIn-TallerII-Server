#include <services/SharedServerAPI/SharedServerAPI.h>

#include <string>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <settings/SettingManager.h>
#include <utils/JSONUtils.h>
#include <iostream>

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

HTTPResponse* SharedServerAPI::doDelete(string uri){
	if (!client->connectToUrl(sharedURL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().DELETE()->setUri(uri);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);
}

Json::Value SharedServerAPI::setObject(string url,string body){

	HTTPResponse* response = doPost(url,body);

	Json::Value res;

	if (response->getCode() == 200){
		res["ok"] = "OK";
	}
	else {
		res["error"] = JSONUtils::stringToJSON(response->getBody())["message"];
	}

	return res;
}

Json::Value SharedServerAPI::updateObject(string url,string body){
	HTTPResponse* response = doPut(url , body);

	Json::Value res;

	if (response->getCode() == 200){
		res["ok"] = "OK";
	}
	else {
		res["error"] = JSONUtils::stringToJSON(response->getBody())["message"];
	}

	return res;
}

Json::Value SharedServerAPI::deleteObject(string url){
	HTTPResponse* response = doDelete(url);

	Json::Value res;

	if (response->getCode() == 204){
		res["ok"] = "OK";
	}
	else {
		res["error"] = JSONUtils::stringToJSON(response->getBody())["message"];
	}

	return res;
}

//skills
Json::Value SharedServerAPI::getSkills(){
	HTTPResponse* response = doGet("/skills");
	Json::Value res = JSONUtils::stringToJSON(response->getBody());
	return res["skills"];
}

Json::Value SharedServerAPI::getSkill(string name){
	HTTPResponse* response = doGet("/skills");
	Json::Value body = JSONUtils::stringToJSON(response->getBody());

	if (body.isMember("error") || !body.isMember("skills")){
		Json::Value error;
		error["error"] = "error on list skills";
		return error;
	}

	Json::Value skills = body["skills"];

	Json::Value skill = JSONUtils::findValue(skills,"name",name);

	if (skill.isMember("error")){
		Json::Value error;
		error["error"] = "skill does not exist.";
		return error;
	}

	return skill;
}

Json::Value SharedServerAPI::setSkill(string name,string description, string category){

	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\" }";
	string url = "/skills/categories/"+category;
	return setObject(url,body);
}

Json::Value SharedServerAPI::updateSkill(string name,string description, string category){
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\", \"category\":\""+category +"\" }";
	string url = "/skills/categories/"+category+"/"+name;

	return updateObject(url,body);
}

//Job positions
Json::Value SharedServerAPI::getJobPositions(){
	HTTPResponse* response = doGet("/job_position");
	Json::Value body = JSONUtils::stringToJSON(response->getBody());
	return body["job_positions"];
}

Json::Value SharedServerAPI::getJobPosition(string name){
	HTTPResponse* response = doGet("/job_positions");
	Json::Value body = JSONUtils::stringToJSON(response->getBody());
	Json::Value positions = body["job_positions"];

	Json::Value pos = JSONUtils::findValue(positions,"name",name);

	if (pos.isMember("error")){
		Json::Value error;
		error["error"] = "job position does not exist.";
		return error;
	}

	return pos;
}

Json::Value SharedServerAPI::setJobPosition(string name,string description, string category){
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\" }";
	string url = "/job_positions/categories/"+category;

	return setObject(url,body);
}


Json::Value SharedServerAPI::updateJobPosition(string name,string description,string category){
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\", \"category\":\""+category +"\" }";
	string url = "/job_positions/categories/"+category+"/"+name;

	return updateObject(url,body);
}

Json::Value SharedServerAPI::deleteJobPosition(string name,string category){
	string url = "/job_positions/categories/"+category+"/"+name;
	return deleteObject(url);
}


SharedServerAPI::~SharedServerAPI() {
	delete client;
}

