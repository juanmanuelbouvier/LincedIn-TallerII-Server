#ifndef SRC_MAIN_HEADERS_EXCEPTION_TOKENEXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_TOKENEXCEPTION_H_

#include <exception/AppServerException.h>

namespace std {

class TokenException : public AppServerException {
public:
	TokenException(string message) : AppServerException(message){};
	virtual ~TokenException(){};
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_EXCEPTION_TOKENEXCEPTION_H_ */
