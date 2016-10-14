#ifndef SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_
#define SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_

#include <services/HTTP/Message/HTTPResponse.h>
#include <services/Server/ServerClient.h>
#include <vector>

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
	HTTPResponse* getSkills();
	HTTPResponse* doGet( string uri );

	vector<string> getsURL();

	virtual ~SharedServerAPI();
};

#endif /* SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_ */
