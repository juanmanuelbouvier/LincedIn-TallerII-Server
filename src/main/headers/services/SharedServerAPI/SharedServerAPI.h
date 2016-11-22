#ifndef SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_
#define SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_

#include <services/HTTP/Message/HTTPResponse.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/Server/ServerClient.h>
#include <vector>
#include <extern/json.h>

using namespace std;

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

	// API Rest
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

#endif /* SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_ */
