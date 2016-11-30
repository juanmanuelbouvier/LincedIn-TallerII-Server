#ifndef SRC_MAIN_SRC_SERVICE_FIREBASE_FIREBASECLIENT_H_
#define SRC_MAIN_SRC_SERVICE_FIREBASE_FIREBASECLIENT_H_

#include <services/Server/ServerClient.h>
#include <services/HTTP/Message/HTTPResponse.h>
#include <extern/json.h>
#include <string>

using namespace std;

class FirebaseClient {
private:
	static HTTPResponse* sendRequest(HTTPRequest* request);
	static HTTPResponse* doPOST( Json::Value body );

public:
	/**
	 * Send notification to user from server using Firebas.
	 * @param Firebase id of dest.
	 * @param Title of notification
	 * @param Body notification
	 * @return True if could be sended
	 */
	static bool sendNotifications(string to,string title,string text);

};

#endif /* SRC_MAIN_SRC_SERVICE_FIREBASE_FIREBASECLIENT_H_ */
