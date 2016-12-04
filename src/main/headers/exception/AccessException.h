#ifndef SRC_MAIN_SRC_EXCEPTION_ACCESSEXCEPTION_H_
#define SRC_MAIN_SRC_EXCEPTION_ACCESSEXCEPTION_H_

#include <exception/AppServerException.h>

using namespace std;

class AccessException : public AppServerException {
public:
	AccessException(string msg) : AppServerException(msg){};
	virtual ~AccessException(){};
};

#endif /* SRC_MAIN_SRC_EXCEPTION_ACCESSEXCEPTION_H_ */
