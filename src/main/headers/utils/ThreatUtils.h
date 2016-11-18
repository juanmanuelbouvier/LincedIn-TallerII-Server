/*
 * ThreatUtils.h
 *
 *  Created on: 17 nov. 2016
 *      Author: tomi
 */

#ifndef SRC_MAIN_SRC_UTILS_THREATUTILS_H_
#define SRC_MAIN_SRC_UTILS_THREATUTILS_H_

class ThreatUtils {
public:
	static void startThreath( void *(*function)(void *), void* arg_function );
};

#endif /* SRC_MAIN_SRC_UTILS_THREATUTILS_H_ */
