#ifndef SRC_MAIN_HEADERS_EXCEPTION_APPSERVEREXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_APPSERVEREXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

class AppServerException : public exception {

private:
	string message;

public:
	virtual const char* what() const throw() {
		return message.c_str();
	};

	AppServerException( string message ) { this->message = message; };

	virtual ~AppServerException(){};
};



#endif /* SRC_MAIN_HEADERS_EXCEPTION_APPSERVEREXCEPTION_H_ */
