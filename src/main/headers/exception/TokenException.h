#ifndef SRC_MAIN_HEADERS_EXCEPTION_TOKENEXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_TOKENEXCEPTION_H_

#include <exception/AppServerException.h>

using namespace std;

class TokenException : public AppServerException {
public:
	TokenException(string message) : AppServerException(message){};
	virtual ~TokenException(){};
};


#endif /* SRC_MAIN_HEADERS_EXCEPTION_TOKENEXCEPTION_H_ */
