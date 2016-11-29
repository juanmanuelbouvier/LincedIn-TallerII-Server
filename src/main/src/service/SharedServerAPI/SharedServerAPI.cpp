#include <services/SharedServerAPI/SharedServerAPI.h>

#include <string>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <settings/SettingManager.h>
#include <utils/JSONUtils.h>
#include <iostream>

using namespace std;

SharedServerAPI::SharedServerAPI() {
	client = new ServerClient();
	sharedURL = SettingManager::getInstance()->getSharedServerURL();
}

HTTPResponse* SharedServerAPI::sendRequest(HTTPRequest* request) {
	HTTPResponse* response = ( client->connectToUrl(sharedURL) ) ? client->sendRequest(request) : ResponseBuilder::createErrorResponse(500,"CANNOT_CONNECT_SHARED");

	return response;
}

HTTPResponse* SharedServerAPI::doGet( string uri ){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->GET()->setUri(uri);
	builder = (RequestBuilder*)builder->appendHeader("connection","keep-alive");
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	delete builder;
	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

HTTPResponse* SharedServerAPI::doPost( string uri, string body ){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->POST()->setUri(uri)->appendHeader("Content-type","application/json")->setBody(body);
	builder = (RequestBuilder*)builder->appendHeader("connection","keep-alive");
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	delete builder;
	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

HTTPResponse* SharedServerAPI::doPut(string uri, string body){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->appendHeader("connection","keep-alive");
	builder = (RequestBuilder*)builder->PUT()->setUri(uri)->appendHeader("Content-type","application/json")->setBody(body);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	delete builder;
	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

HTTPResponse* SharedServerAPI::doDelete(string uri){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->DELETE()->setUri(uri);
	builder = (RequestBuilder*)builder->appendHeader("connection","keep-alive");
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	delete builder;
	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

Json::Value SharedServerAPI::processResponse(HTTPResponse* response, int expectedCode) {
	Json::Value res;

	if (response->getCode() == expectedCode){
		res["ok"] = "OK";
	} else {
		res["error"] = response->getBody();
	}
	delete response;
	return res;
}

Json::Value SharedServerAPI::setObject(string url,string body){

	HTTPResponse* response = doPost(url,body);

	return processResponse(response,201);
}

Json::Value SharedServerAPI::updateObject(string url,string body){
	HTTPResponse* response = doPut(url , body);

	return processResponse(response,200);
}

Json::Value SharedServerAPI::deleteObject(string url){
	HTTPResponse* response = doDelete(url);
	return processResponse(response,204);
}

//skills
Json::Value SharedServerAPI::getSkills(){
	return getObjectsFromResponse("/skills","skills");
}

Json::Value SharedServerAPI::getSkill(string name){
	Json::Value skills = getSkills();
	return findObjectFromResponse(skills,"Skills","name",name);
}

Json::Value SharedServerAPI::setSkill(string name,string description, string category){

	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\" }";
	string url = "/skills/categories/"+category;
	return setObject(url,body);
}

Json::Value SharedServerAPI::updateSkill(string name,string new_name,string description,string category,string new_category){
	string n_name = new_name.empty()? name : new_name;
	string n_category = new_category.empty()? category : new_category;
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ n_name +"\", \"category\":\""+n_category +"\" }";
	string url = "/skills/categories/"+category+"/"+name;

	return updateObject(url,body);
}

Json::Value SharedServerAPI::deleteSkill(string name,string category){
	string url = "/skills/categories/"+category+"/"+name;
	return deleteObject(url);
}

//Job positions
Json::Value SharedServerAPI::getJobPositions(){
	return getObjectsFromResponse("/job_positions","job_positions");
}

Json::Value SharedServerAPI::getJobPosition(string name){
	Json::Value job_positions = getJobPositions();
	return findObjectFromResponse(job_positions,"Job positions","name",name);
}

Json::Value SharedServerAPI::getObjectsFromResponse(string uri, string value) {
	HTTPResponse* response = doGet(uri);
	Json::Value body = JSONUtils::stringToJSON(response->getBody());
	delete response;
	Json::Value error;
	error["error"] = "Error on get " + value;
	return ( body.isMember("error") || !body.isMember(value) ) ? error : body[value];

}

Json::Value SharedServerAPI::findObjectFromResponse(Json::Value objects, string value,string tag_in_value, string goal) {
	Json::Value error;
	error["error"] = "Cannot find " + tag_in_value + " " + goal + " in " + value;
	Json::Value found = ( !objects.isArray() ) ? error : JSONUtils::findValue(objects,tag_in_value,goal);
	return ( found.isMember("error") ) ? error : found;
}

Json::Value SharedServerAPI::setJobPosition(string name,string description, string category){
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ name +"\" }";
	string url = "/job_positions/categories/"+category;

	return setObject(url,body);
}


Json::Value SharedServerAPI::updateJobPosition(string name,string new_name,string description,string category,string new_category){
	string n_name = new_name.empty()? name : new_name;
	string n_category = new_category.empty()? category : new_category;
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ n_name +"\", \"category\":\""+n_category +"\" }";
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

