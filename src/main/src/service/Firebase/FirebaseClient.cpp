#include <services/Firebase/FirebaseClient.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <settings/SettingManager.h>
#include <utils/JSONUtils.h>
#include <services/Logger/Logger.h>

using namespace std;

#define FIREBASE_URI "/fcm/send"

FirebaseClient::FirebaseClient(){
	client = new ServerClient();
	firebaseURL = SettingManager::getInstance()->getFirebaseURL();
	apiKey = SettingManager::getInstance()->getFirebaseApiKey();
}

HTTPResponse* FirebaseClient::sendRequest(HTTPRequest* request) {
	HTTPResponse* response = ( client->connectToUrl(firebaseURL) ) ? client->sendRequest(request) : ResponseBuilder::createErrorResponse(500,"CANNOT_CONNECT_FIREBASE");

	return response;
}

HTTPResponse* FirebaseClient::doPOST( Json::Value body){

	RequestBuilder* builder = new RequestBuilder();
	builder = (RequestBuilder*)builder->POST()->setUri(FIREBASE_URI);

	builder = (RequestBuilder*)builder->appendHeader("Content-Type","application/json");
	builder = (RequestBuilder*)builder->appendHeader("Authorization","key=" + apiKey);


	string body_string = JSONUtils::JSONToString(body);

	builder = (RequestBuilder*)builder->setBody(body_string);

	HTTPRequest* theRequest = builder->build();
	delete builder;

	HTTPResponse* response = sendRequest(theRequest);
	delete theRequest;
	return response;
}

bool FirebaseClient::sendNotifications(string to,string title,string text){
	Json::Value body;
	body["to"] = to;

	Json::Value notification;
	notification["title"] = title;
	notification["text"] = text;

	body["notification"] = notification;

	HTTPResponse* response = doPOST(body);
	int code = response->getCode();
	delete response;

	if (code == 401){
		LOG("cannot conect with firebase, error on authorizate",ERROR);
		return false;
	}
	else if (code == 200){
		return true;
	}

	return false;

}

FirebaseClient::~FirebaseClient(){
	delete client;
}
