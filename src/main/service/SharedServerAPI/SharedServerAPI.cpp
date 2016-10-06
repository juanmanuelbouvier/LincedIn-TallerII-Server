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
	if (!client->connectToUrl(SHARED_SERVER_URL)) {
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
	RequestBuilder builder;
	HTTPRequest* theRequest = builder.GET()->setUri("/skills")->build();
	return client->sendRequest(theRequest);


}


SharedServerAPI::~SharedServerAPI() {
	delete client;
	if(instaceAPI){
		instaceAPI = NULL;
	}
}

