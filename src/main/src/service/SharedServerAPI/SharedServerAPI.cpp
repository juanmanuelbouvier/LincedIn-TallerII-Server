#include <services/SharedServerAPI/SharedServerAPI.h>

#include <string>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <settings/SettingManager.h>
#include <utils/JSONUtils.h>
#include <iostream>
#include <utils/DateUtils.h>
#include <services/Logger/Logger.h>
#include <services/DB/DBs.h>
#include <services/DB/DBManager.h>
#include <services/DB/DB.h>
using namespace std;

#define MAX_AGE_CACHE 60*60*5 //5 hour

bool SharedServerCache::notDefeated(string endpoint) {
	Json::Value data = DBManager::getDB(Databases::DB_SHARED_SERVER_CACHE)->getJSON(endpoint);
	if (data.isMember("age")) {
		int now = DateUtils::timestamp();
		int age = data["age"].asInt();
		LOG("Endpoint cache " + endpoint + (( age + MAX_AGE_CACHE >= now ) ? " is alive" : " is defeated"),DEBUG );
		return ( age + MAX_AGE_CACHE >= now );
	}
	return false;
}
Json::Value SharedServerCache::get(string endpoint) {
	Json::Value data = DBManager::getDB(Databases::DB_SHARED_SERVER_CACHE)->getJSON(endpoint);
	if (data.isMember("data")) {
		return data["data"];
	}
	return Json::nullValue;
}

Json::Value SharedServerCache::store(string endpoint, Json::Value data) {
	Json::Value toStore;
	toStore["data"] = data;
	toStore["age"] = DateUtils::timestamp();
	DBManager::getDB(Databases::DB_SHARED_SERVER_CACHE)->storeJSON(endpoint,toStore);
	return data;
}
bool SharedServerCache::setDefeat(string endpoint) {
	Json::Value data = DBManager::getDB(Databases::DB_SHARED_SERVER_CACHE)->getJSON(endpoint);
	if (data.isMember("age")) {
		data["age"] = 0;
		return DBManager::getDB(Databases::DB_SHARED_SERVER_CACHE)->storeJSON(endpoint,data);
	}
	return true;
}

SharedServerAPI::SharedServerAPI() {
	client = new ServerClient();
	sharedURL = SettingManager::getInstance()->getSharedServerURL();
}

HTTPResponse* SharedServerAPI::sendRequest(HTTPRequest* request) {
	int init = DateUtils::timestamp();
	HTTPResponse* response = ( client->connectToUrl(sharedURL) ) ? client->sendRequest(request) : ResponseBuilder::createErrorResponse(500,"CANNOT_CONNECT_SHARED");
	int time = DateUtils::timestamp() - init;
	Log("Shared Server response of " + request->getURI() +" in " + to_string(time) + " seconds" + ((response->getCode() == 500) ? " (timeout)" : ""),DEBUG);
	return response;
}

HTTPResponse* SharedServerAPI::doGet( string uri ){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->GET()->setUri(uri);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	delete builder;
	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

HTTPResponse* SharedServerAPI::doPost( string uri, string body ){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->POST()->setUri(uri)->appendHeader("Content-Type","application/json")->setBody(body);
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	HTTPRequest* theRequest = builder->build();
	delete builder;
	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

HTTPResponse* SharedServerAPI::doPut(string uri, string body){
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->PUT()->setUri(uri)->appendHeader("Content-Type","application/json")->setBody(body);
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
	builder = (RequestBuilder*)builder->appendHeader("Host",string(sharedURL));
	builder = (RequestBuilder*)builder->appendHeader("Connection","close");
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
	Json::Value result = processResponse(response,214);
	if (result.isMember("error")) {
		result = processResponse(response,204);
	}
	delete response;
	return result;
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
	SharedServerCache::setDefeat("/skills");
	return setObject(url,body);
}

Json::Value SharedServerAPI::updateSkill(string name,string new_name,string description,string category,string new_category){
	string n_name = new_name.empty()? name : new_name;
	string n_category = new_category.empty()? category : new_category;
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ n_name +"\", \"category\":\""+n_category +"\" }";
	string url = "/skills/categories/"+category+"/"+name;
	SharedServerCache::setDefeat("/skills");
	return updateObject(url,body);
}

Json::Value SharedServerAPI::deleteSkill(string name,string category){
	string url = "/skills/categories/"+category+"/"+name;
	SharedServerCache::setDefeat("/skills");
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
	if (SharedServerCache::notDefeated(uri)) {
		Json::Value cacheData = SharedServerCache::get(uri);
		if (!cacheData.isNull()) {
			Log("SharedServer uri " + uri + " is in cache. Load it",DEBUG);
			return cacheData;
		}
	}
	HTTPResponse* response = doGet(uri);
	Json::Value body = JSONUtils::stringToJSON(response->getBody());
	delete response;
	Json::Value error;
	error["error"] = "Error on get " + value;
	return ( body.isMember("error") || !body.isMember(value) ) ? error : SharedServerCache::store(uri,body[value]);
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
	SharedServerCache::setDefeat("/job_positions");
	return setObject(url,body);
}


Json::Value SharedServerAPI::updateJobPosition(string name,string new_name,string description,string category,string new_category){
	string n_name = new_name.empty()? name : new_name;
	string n_category = new_category.empty()? category : new_category;
	string body = "{ \"description\":\""+ description +"\", \"name\":\""+ n_name +"\", \"category\":\""+n_category +"\" }";
	string url = "/job_positions/categories/"+category+"/"+name;
	SharedServerCache::setDefeat("/job_positions");
	return updateObject(url,body);
}

Json::Value SharedServerAPI::deleteJobPosition(string name,string category){
	string url = "/job_positions/categories/"+category+"/"+name;
	SharedServerCache::setDefeat("/job_positions");
	return deleteObject(url);
}


SharedServerAPI::~SharedServerAPI() {
	delete client;
}

