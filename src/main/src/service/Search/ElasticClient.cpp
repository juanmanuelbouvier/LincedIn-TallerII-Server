#include <services/Searcher/ElasticClient.h>
#include <utils/JSONUtils.h>

ElasticClient::ElasticClient(string aHost) {
	client = new ServerClient();
	host = aHost;
}

bool ElasticClient::isAlive() {
	if (client->connectToUrl(host)) {
		RequestBuilder* builder = new RequestBuilder();
		builder = builder->GET()->setUri("/");
		Json::Value res = sendRequest(builder);
		if (res["_code"].asString() != "408" ) {
			return true;
		}
	}
	return false;
}

bool ElasticClient::index(string index, string type, string id, Json::Value data) {
	RequestBuilder* builder = new RequestBuilder();
	string indexPath = id.empty() ? "" : "/" + id;
	builder = builder->POST()->setBody(JSONUtils::JSONToString(data))->setUri("/" + index + "/" + type + indexPath);
	Json::Value result = this->sendRequest(builder);
	return (result.isMember("response") && result["response"].isMember("result") && ( result["response"]["result"].asString() == "created" || result["response"]["result"].asString() == "updated")  );
}

Json::Value ElasticClient::sendRequest(RequestBuilder* builder) {
	builder = (RequestBuilder*)builder->appendHeader("Host",host);
	HTTPRequest* req = builder->build();
	delete builder;
	if ( !client->connectToUrl(host) ) {
		Json::Value empty;
		return empty;
	}
	HTTPResponse* res = client->sendRequest(req);
	delete req;
	Json::Value response;
	if (!res->getBody().empty()) {
		response["response"] = JSONUtils::stringToJSON(res->getBody());
	}
	response["_code"] = res->getCode();
	return response;
}

Json::Value ElasticClient::search(string index, string type, string query) {
	RequestBuilder* builder = new RequestBuilder();
	builder = builder->GET()->setUri("/" + index + "/" + type + "/_search")->setQuery("q=" + query + "&default_operator=or");
	Json::Value result = sendRequest(builder);
	if ( result.isMember("response") && result["response"].isMember("hits") && result["response"]["hits"].isMember("hits") ) {
		return result["response"]["hits"]["hits"];
	}
	result = Json::Value(Json::arrayValue);
	return result;
}

Json::Value ElasticClient::get(string index, string type, string id) {
	RequestBuilder* builder = new RequestBuilder();
	builder = builder->GET()->setUri("/" + index + "/" + type + "/" + id);
	Json::Value result = sendRequest(builder);
	if ( result.isMember("found") && result["found"].asBool() ) {
		return result["response"]["_source"];
	}
	result = Json::Value(Json::nullValue);
	return result;
}

ElasticClient::~ElasticClient() {
	delete client;
}

