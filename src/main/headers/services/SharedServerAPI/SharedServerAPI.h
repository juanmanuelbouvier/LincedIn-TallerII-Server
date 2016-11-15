#ifndef SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_
#define SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_

#include <services/HTTP/Message/HTTPResponse.h>
#include <services/Server/ServerClient.h>
#include <vector>
#include <extern/json.h>

using namespace std;

class SharedServerAPI {
private:
	ServerClient* client;
	string sharedURL;

	Json::Value setObject(string url,string body);
	Json::Value updateObject(string url,string body);
	Json::Value deleteObject(string url);


public:
	SharedServerAPI();

	// API Rest
	Json::Value getSkills();
	Json::Value getSkill(string name);
	Json::Value setSkill(string name,string description, string category);
	Json::Value updateSkill(string name,string description, string category);

	Json::Value getJobPositions();
	Json::Value getJobPosition(string name);
	Json::Value setJobPosition(string name,string description, string category);
	Json::Value updateJobPosition(string name,string description, string category);
	Json::Value deleteJobPosition(string name,string category);

	HTTPResponse* doGet( string uri );
	HTTPResponse* doPost(string uri, string body);
	HTTPResponse* doPut(string uri, string body);
	HTTPResponse* doDelete(string uri);

	vector<string> getsURL();

	virtual ~SharedServerAPI();
};

#endif /* SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_ */
