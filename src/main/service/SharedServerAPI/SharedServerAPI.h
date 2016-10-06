#ifndef SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_
#define SRC_MAIN_SERVICE_SHAREDSERVERAPI_SHAREDSERVERAPI_H_

#include <iostream>
#include "../MongooseServer/ServerClient.h"
#include "../HTTP/Message/HTTPRequest.h"
#include "../HTTP/Message/HTTPResponse.h"
#include "../HTTP/Message/HTTPMessageBuilder.h"

using namespace std;

#define SHARED_SERVER_LOCAL_URL "localhost:8080"
#define SHARED_SERVER_HEROKU_URL "lincedin.herokuapp.com:80"

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
