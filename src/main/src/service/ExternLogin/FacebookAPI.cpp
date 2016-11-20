#include <services/ExternLogin/FacebookAPI.h>
#include <services/Logger/Logger.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/JSONUtils.h>

#define SECURE "https://"
#define FB_GRAPH "graph.facebook.com"
#define FB_PORT "80"
#define FB_PATH "/me"
#define FB_QUERY "fields=email,last_name,middle_name,birthday,first_name&access_token="

const string FacebookAPI::FB_BirthdayDateFormat = "%m/%d/%Y";


HTTPResponse* FacebookAPI::sendRequest(string path, string query ) {
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->GET();
	builder = (RequestBuilder*)builder->setUri(path);
	if (!query.empty()){
		builder = (RequestBuilder*)builder->setQuery(query);
	}
	builder = (RequestBuilder*)builder->appendHeader("Host",string(FB_GRAPH))->appendHeader("Cache-Control","no-cache");
	HTTPRequest* request = builder->build();
	HTTPResponse* response = client->sendRequest( request );

	delete builder;
	delete request;

	return response;
}

Json::Value FacebookAPI::parseResponse( HTTPResponse* response ) {
	Json::Value body;
	if (response->getCode() != 200) {
		body = JSONUtils::stringToJSON( response->getBody() );
		body["response"]["code"] = response->getCode();
		body["response"]["phrase"] = response->getPhrase();
		body["error"] = "Graph response error";
		delete response;
		return body;
	}
	body = JSONUtils::stringToJSON( response->getBody() );
	delete response;
	return body;
}

bool logTheError(string line, string url) {
	Log("FacebookAPI.cpp::" + to_string(__LINE__) + ". Unable to Connect with " + url, WARNING);
	return false;
}

bool FacebookAPI::connect() {
	string url = string(SECURE) + string(FB_GRAPH);
	return (client->connectToUrl( url )) ? true : logTheError(to_string(__LINE__),url);
}

Json::Value FacebookAPI::getInfoFromToken( string token ) {
	Json::Value infoError;
	infoError["error"] = "Error";
	string query = FB_QUERY + token;
	return (connect()) ? parseResponse( sendRequest(string(FB_PATH),query) ) : infoError;
}

