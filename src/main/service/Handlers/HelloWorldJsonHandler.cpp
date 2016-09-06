/*
 * HelloWorldJsonHandler.cpp
 *
 *  Created on: 5 sep. 2016
 *      Author: tomi
 */

#include "HelloWorldJsonHandler.h"
#include "../Logger/Logger.h"

HelloWorldJsonHandler::HelloWorldJsonHandler() {
}

char* HelloWorldJsonHandler::handle(){
	Json::Value event;
	Json::Value vec(Json::arrayValue);
	vec.append(Json::Value(1));
	vec.append(Json::Value(2));
	vec.append(Json::Value(3));

	event["titulo"] = "Hello World Test to LincedIn Taller ii";
	Json::Value integrantes(Json::arrayValue);
	event["integrantes"] = integrantes;

	Json::Value tomi;
	tomi["nombre"] = "Tomas Bert";
	tomi["padron"] = 95606;

	Json::Value jmb;
	jmb["nombre"] = "Juan Manuel Bouvier";
	jmb["padron"] = 95505;

	event["integrantes"].append(tomi);
	event["integrantes"].append(jmb);

	Json::FastWriter writer;
	writer.omitEndingLineFeed();
	string toReturn = writer.write(event);

	string body = "HTTP/1.0 200 OK\r\n\r\nContent-type:application/json\r\n" + toReturn;
	return (char*)body.c_str();
}

HelloWorldJsonHandler::~HelloWorldJsonHandler(){
}
