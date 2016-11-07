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

	SharedServerAPI();

	static SharedServerAPI* instaceAPI;

public:

	//Singleton
	static SharedServerAPI* getInstance();
	static void deleteInstance();

	// API Rest
	Json::Value getSkills();
	Json::Value getSkill(string name);
	Json::Value setSkill(string name,string description, string category);
	Json::Value updateSkill(string name,string description, string category);
	HTTPResponse* doGet( string uri );
	HTTPResponse* doPost(string uri, string body);
	HTTPResponse* doPut(string uri, string body);
	HTTPResponse* doDelete(string uri);

	vector<string> getsURL();

	virtual ~SharedServerAPI();
};

#endif /* SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_ */
