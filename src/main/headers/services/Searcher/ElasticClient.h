#ifndef SRC_MAIN_SRC_SERVICE_SEARCH_ELASTICCLIENT_H_
#define SRC_MAIN_SRC_SERVICE_SEARCH_ELASTICCLIENT_H_

#include <string>
#include <extern/json.h>
#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>

class ElasticClient {
private:
	string host;
	ServerClient* client;

	Json::Value sendRequest( RequestBuilder* builder );

public:
	ElasticClient(string host);

	bool isAlive();

	bool index(string index, string type, string id, Json::Value data);
	Json::Value get(string index, string type, string id);
	Json::Value search(string index, string type, string query);

	virtual ~ElasticClient();
};


#endif /* SRC_MAIN_SRC_SERVICE_SEARCH_ELASTICCLIENT_H_ */
