#ifndef SRC_MAIN_HEADERS_EXCEPTION_USEREXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_USEREXCEPTION_H_

#include <exception/AppServerException.h>

namespace std {

class UserException : public AppServerException {
public:
	UserException(string message) : AppServerException(message){};
	virtual ~UserException(){};
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_EXCEPTION_USEREXCEPTION_H_ */
