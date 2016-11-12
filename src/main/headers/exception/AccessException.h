#ifndef SRC_MAIN_SRC_EXCEPTION_ACCESSEXCEPTION_H_
#define SRC_MAIN_SRC_EXCEPTION_ACCESSEXCEPTION_H_

#include <exception>

using namespace std;


class AccessException : public exception {
private:
	string message;
public:
	AccessException(string msg){message = msg;};
	virtual const char* what() const throw() {
		return message.c_str();
	}
	virtual ~AccessException(){};
};

#endif /* SRC_MAIN_SRC_EXCEPTION_ACCESSEXCEPTION_H_ */
