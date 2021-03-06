#ifndef SRC_MAIN_SRC_SERVICE_EXTERNLOGIN_FACEBOOKAPI_H_
#define SRC_MAIN_SRC_SERVICE_EXTERNLOGIN_FACEBOOKAPI_H_

#include <string>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPRequest.h>
#include <services/HTTP/Message/HTTPResponse.h>
#include <services/Server/ServerClient.h>

using namespace std;

class FacebookAPI {
private:
	ServerClient* client;

	Json::Value parseResponse( HTTPResponse* response );
	HTTPResponse* sendRequest( string path, string query);

	bool connect();

public:
	FacebookAPI(){ client = new ServerClient(); };

	/**
	 * Constant who has a format of date specified in Facebook Docs.
	 */
	static const string FB_BirthdayDateFormat;

	/**
	 * Get information of FB TOKEN.
	 * @param Facebook Token as String
	 * @return Json Value with the token information.
	 */
	Json::Value getInfoFromToken( string token );

	virtual ~FacebookAPI(){ delete client; };
};

#endif /* SRC_MAIN_SRC_SERVICE_EXTERNLOGIN_FACEBOOKAPI_H_ */
