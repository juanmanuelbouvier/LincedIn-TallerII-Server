#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/JSONUtils.h>
#include "LincedInServerConfig.h"
#include <services/HTTP/HTTPResponseConstants.h>

using namespace std;

MessageBuilder::MessageBuilder() {
	body = "";
}

MessageBuilder* MessageBuilder::setBody(string aBody){
	body = aBody;
	return this;
}

MessageBuilder* MessageBuilder::addHeader(map<string,string> fullHeader){
	headers = fullHeader;
	return this;
}

MessageBuilder* MessageBuilder::appendHeader(string key, string value){
	headers[key] = value;
	return this;
}

MessageBuilder* MessageBuilder::joinHeader(map<string,string> otherHeaders){
	headers.insert(otherHeaders.begin(), otherHeaders.end());
	return this;
}

MessageBuilder::~MessageBuilder(){

}





RequestBuilder::RequestBuilder() : MessageBuilder() {
	method 	= "GET";
	uri		= "/";
	query 	= "";
}

RequestBuilder* RequestBuilder::setMethod(string aMethod){
	method = aMethod;
	return this;
}

RequestBuilder* RequestBuilder::setBody(string theBody){
	body = theBody;
	return this;
}

RequestBuilder* RequestBuilder::GET(){
	setMethod("GET");
	return this;
}

RequestBuilder* RequestBuilder::PUT(){
	setMethod("PUT");
	return this;
}

RequestBuilder* RequestBuilder::DELETE(){
	setMethod("DELETE");
	return this;
}

RequestBuilder* RequestBuilder::POST(){
	setMethod("POST");
	return this;
}

RequestBuilder* RequestBuilder::setUri(string aUri){
	uri = aUri;
	return this;
}

RequestBuilder* RequestBuilder::setQuery(string aQuery){
	query = aQuery;
	return this;
}

HTTPRequest* RequestBuilder::build(){
	HTTPRequest* theRequest = new HTTPRequest(method, uri, query, body, headers);
	return theRequest;
};

RequestBuilder::~RequestBuilder(){

}





ResponseBuilder::ResponseBuilder() : MessageBuilder() {
	code 	= "200";
	phrase 	= "OK";
}

Json::Value ResponseBuilder::createErrorJSON(string message,int internal_code){
	Json::Value json;
	json["code"] = internal_code;
	json["status"] = "ERROR";
	json["message"] = "ERROR. " + message;
	Json::Value metadata;
	metadata["version"] = to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR);
	json["metadata"] = metadata;

	return json;
}

ResponseBuilder* ResponseBuilder::setCode(string theCode){
	code = theCode;
	return this;
}

ResponseBuilder* ResponseBuilder::setCodeAndPhrase(string theCode,string thePhrase){
	setCode(theCode);
	phrase = thePhrase;
	return this;
}

HTTPResponse* ResponseBuilder::build(){
	HTTPResponse* theResponse = new HTTPResponse(code, phrase, body, headers);
	return theResponse;
}

HTTPResponse* ResponseBuilder::createEmptyResponse(int code,string message){
	Json::Value json;
	json["code"] = code;
	json["status"] = "OK";
	json["message"] =  message;
	Json::Value metadata;
	metadata["version"] = to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR);
	json["metadata"] = metadata;

	return createJsonResponse(code,json);
}


HTTPResponse* ResponseBuilder::createJsonResponse(int code, Json::Value body) {
	return createJsonResponse(code, JSONUtils::JSONToString(body) );
}

HTTPResponse* ResponseBuilder::createJsonResponse(int code, string body){
	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-type","application/json")->setBody(body);
	builder = (ResponseBuilder*)builder->setCodeAndPhrase(std::to_string(code),phraseByCode(code));
	HTTPResponse* res = builder->build();
	delete builder;
	return res;
}

HTTPResponse* ResponseBuilder::createErrorResponse(int code, string error){
	return createErrorResponse(code,error,code);
}

HTTPResponse* ResponseBuilder::createErrorResponse(int code, string error,int internal_code){

	Json::Value error_json = createErrorJSON(error,internal_code);

	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-type","application/json")->setBody(JSONUtils::JSONToString(error_json));
	builder = (ResponseBuilder*)builder->setCodeAndPhrase(std::to_string(code),phraseByCode(code));
	HTTPResponse* res = builder->build();
	delete builder;
	return res;
}

ResponseBuilder::~ResponseBuilder(){

}
