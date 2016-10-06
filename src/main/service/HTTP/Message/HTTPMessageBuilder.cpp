#include "../Message/HTTPMessageBuilder.h"

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

ResponseBuilder* ResponseBuilder::setCode(int theCode){
	code = theCode;
	return this;
}

ResponseBuilder* ResponseBuilder::setCodeAndPhrase(int theCode,string thePhrase){
	setCode(theCode);
	phrase = thePhrase;
	return this;
}

HTTPResponse* ResponseBuilder::build(){
	HTTPResponse* theResponse = new HTTPResponse(code, phrase, body, headers);
	return theResponse;
}

ResponseBuilder::~ResponseBuilder(){

}
