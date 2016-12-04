#ifndef SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_
#define SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_

#include <services/HTTP/Message/HTTPResponse.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/Server/ServerClient.h>
#include <vector>
#include <extern/json.h>

using namespace std;

/**
 * SharedServerAPI abstract all request of SharedServer.
 */

class SharedServerAPI {
private:
	ServerClient* client;
	string sharedURL;

	Json::Value processResponse(HTTPResponse* response, int expectedCode);
	Json::Value setObject(string url,string body);
	Json::Value updateObject(string url,string body);
	Json::Value deleteObject(string url);
	HTTPResponse* sendRequest(HTTPRequest* request);

	Json::Value getObjectsFromResponse(string uri, string value);
	Json::Value findObjectFromResponse(Json::Value objects, string value, string tag_in_value, string goal);

public:
	SharedServerAPI();

	Json::Value getSkills();
	Json::Value getSkill(string name);
	Json::Value setSkill(string name,string description, string category);
	Json::Value updateSkill(string name,string new_name,string description,string category,string new_category);
	Json::Value deleteSkill(string name, string category);

	Json::Value getJobPositions();
	Json::Value getJobPosition(string name);
	Json::Value setJobPosition(string name,string description, string category);
	Json::Value updateJobPosition(string name,string new_name,string description,string category,string new_category);
	Json::Value deleteJobPosition(string name,string category);

	HTTPResponse* doGet( string uri );
	HTTPResponse* doPost(string uri, string body);
	HTTPResponse* doPut(string uri, string body);
	HTTPResponse* doDelete(string uri);

	virtual ~SharedServerAPI();
};

/**
 * Simple Cache to avoid multiple response to SharedServer.
 */
class SharedServerCache {
public:
	/**
	 * Check if endpoint is alive on Cache
	 * @param endpoint
	 * @return True if alive, false if defeated
	 */
	static bool notDefeated(string endpoint);

	/**
	 * Get cached data.
	 * @note This metod dont check time of cache data.
	 * @param endpoint
	 * @return Json Cached data
	 */
	static Json::Value get(string endpoint);

	/**
	 * Store data in cache
	 * @param endpoint to chache
	 * @param data to cache
	 * @return data who was cache.
	 */
	static Json::Value store(string endpoint, Json::Value data);

	/**
	 * Set Defeat on cache data
	 * @param key of chache to defeat
	 * @return True if cache is defeated
	 */
	static bool setDefeat(string endpoint);
};

#endif /* SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_ */
