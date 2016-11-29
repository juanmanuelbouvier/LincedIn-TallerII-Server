#ifndef SRC_MAIN_SRC_SERVICE_FIREBASE_FIREBASECLIENT_H_
#define SRC_MAIN_SRC_SERVICE_FIREBASE_FIREBASECLIENT_H_

#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPResponse.h>
#include <extern/json.h>
#include <string>

using namespace std;

class FirebaseClient {
private:
	ServerClient* client;
	string firebaseURL;
	string apiKey;

	HTTPResponse* sendRequest(HTTPRequest* request);
	HTTPResponse* doPOST( Json::Value body );

public:
	FirebaseClient();
	bool sendNotifications(string to,string title,string text);
	~FirebaseClient();
};

#endif /* SRC_MAIN_SRC_SERVICE_FIREBASE_FIREBASECLIENT_H_ */
