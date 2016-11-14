#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/JSONUtils.h>

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
	code 	= 200;
	phrase 	= "OK";
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

HTTPResponse* ResponseBuilder::createJsonResponse(int code, Json::Value body) {
	return createJsonResponse(code, JSONUtils::JSONToString(body) );
}

HTTPResponse* ResponseBuilder::createJsonResponse(int code, string body){
	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-type","application/json")->setBody(body);
	builder = (ResponseBuilder*)builder->setCode(std::to_string(code));
	return builder->build();
}

HTTPResponse* ResponseBuilder::createErrorResponse(int code, string error){
	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-type","text/html")->setBody(error);
	builder = (ResponseBuilder*)builder->setCodeAndPhrase(std::to_string(code),"ERROR");
	return builder->build();
}

ResponseBuilder::~ResponseBuilder(){

}
