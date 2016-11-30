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
	/**
	 * Create Elastic Search client who connect with host.
	 * @param Host of elastic API client
	 */
	ElasticClient(string host);

	/**
	 * Check if Elastic is alive.
	 * @return True if could connect to Elastic
	 */
	bool isAlive();

	/**
	 * Index Json Value (document) in <elastic>/index/type/id
	 * @param The index
	 * @param Type of document (e.j User)
	 * @param Id of de document. If empty the id TODO (lo crea elastic)
	 * @return True if the index was create.
	 */
	bool index(string index, string type, string id, Json::Value data);

	/**
	 * Get document who was store in <elastic>/index/type/id
	 * @param The index
	 * @param Type of document (e.j User)
	 * @param Id of de document.
	 * @return Document in Json Value (if the documen non-exist, return empty Value)
	 */
	Json::Value get(string index, string type, string id);

	/**
	 * Search document in <elastic>/index/type/_search?query
	 * @param The index
	 * @param Type of document (e.j User)
	 * @param Query with the elastic standard query (read Elastic Get Api).
	 * @return Json Value who contains hits of the search.
	 */
	Json::Value search(string index, string type, string query, bool onlyID = false);

	virtual ~ElasticClient();
};


#endif /* SRC_MAIN_SRC_SERVICE_SEARCH_ELASTICCLIENT_H_ */
