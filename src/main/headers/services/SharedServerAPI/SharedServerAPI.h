#ifndef SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_
#define SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_

#include <services/HTTP/Message/HTTPResponse.h>
#include <services/Server/ServerClient.h>

using namespace std;

class SharedServerAPI {
private:
	ServerClient* client;

	SharedServerAPI();

	static SharedServerAPI* instaceAPI;

public:

	//Singleton
	static SharedServerAPI* getInstance();

	// API Rest
	HTTPResponse* getSkills();

	virtual ~SharedServerAPI();
};

#endif /* SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_ */
