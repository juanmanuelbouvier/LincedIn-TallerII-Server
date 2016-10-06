/*
 * SharedServerAPI.cpp
 *
 *  Created on: 6 oct. 2016
 *      Author: tomi
 */

#include "SharedServerAPI.h"

using namespace std;

SharedServerAPI* SharedServerAPI::instaceAPI = NULL;


SharedServerAPI::SharedServerAPI() {
	client = new ServerClient();
	if (!client->connectToUrl(SHARED_SERVER_LOCAL_URL)) {
		delete client;
	}

}

SharedServerAPI* SharedServerAPI::getInstance(){
	if (!instaceAPI) {
		instaceAPI = new SharedServerAPI();
	}
	return instaceAPI;
}


HTTPResponse* SharedServerAPI::getSkills(){
	if (!client->connectToUrl(SHARED_SERVER_LOCAL_URL)){
		return NULL;
	}
	RequestBuilder* builder = RequestBuilder().GET()->setUri("/skills");
	builder = (RequestBuilder*)builder->appendHeader("Host",string(SHARED_SERVER_LOCAL_URL));
	HTTPRequest* theRequest = builder->build();
	return client->sendRequest(theRequest);


}


SharedServerAPI::~SharedServerAPI() {
	delete client;
	if(instaceAPI){
		instaceAPI = NULL;
	}
}

