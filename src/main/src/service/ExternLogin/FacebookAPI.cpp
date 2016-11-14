#include <services/ExternLogin/FacebookAPI.h>
#include <services/Logger/Logger.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/JSONUtils.h>

#define SECURE "https://"
#define FB_GRAPH "graph.facebook.com"
#define FB_PORT "80"
#define FB_PATH "/me"
#define FB_QUERY "fields=name,email,last_name,middle_name,first_name&access_token="

HTTPResponse* FacebookAPI::sendRequest( string query ) {
	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->GET();
	builder = (RequestBuilder*)builder->setUri(string(FB_PATH))->setQuery(query);
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
		delete response;
		return body;
	}
	body = JSONUtils::stringToJSON( response->getBody() );
	delete response;
	return body;
}

Json::Value FacebookAPI::getInfoFromToken( string token ) {
	Json::Value info;
	string url = string(SECURE) + string(FB_GRAPH);
	if ( !client->connectToUrl( url ) ) {
		Log("FacebookAPI.cpp::" + to_string(__LINE__) + ". Unable to Connect with " + url, WARNING);
		info["error"] = "Error";
		return info;
	}

	string query = FB_QUERY + token;
	info = parseResponse( sendRequest(query) );

	return info;
}

