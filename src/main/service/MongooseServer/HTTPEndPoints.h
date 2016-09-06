/*
 * HTTPEndPoints.h
 *
 *  Created on: 6 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_HTTPENDPOINTS_H_
#define SRC_MAIN_HTTPENDPOINTS_H_

#include <map>
#include <iostream>
#include "../Handlers/Handler.h"
#include "../Handlers/HelloWorldJsonHandler.h"
#include "../Logger/Logger.h"
#include "mongoose/mongoose.h"

using namespace std;


class HTTPEndPoints {

private:

	map<string,Handler*> HTTPHandlers;

public:
	HTTPEndPoints();

	Handler* getEndPoint(string endpoint);

	/*Handlers*/
	static void helloWorld(struct mg_connection* nc, int ev, void* ev_data);

	virtual ~HTTPEndPoints();
};

#endif /* SRC_MAIN_HTTPENDPOINTS_H_ */
