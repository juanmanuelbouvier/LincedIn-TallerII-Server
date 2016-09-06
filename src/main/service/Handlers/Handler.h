/*
 * AbstractHandler.h
 *
 *  Created on: 5 sep. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_
#define SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_


class Handler {

public:
	virtual char* handle(/* HTTPRequest */) = 0;
	virtual ~Handler(){};
};


#endif /* SRC_MAIN_SERVICE_HANDLERS_HANDLER_H_ */
