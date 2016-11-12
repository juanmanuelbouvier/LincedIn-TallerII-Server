#ifndef SRC_MAIN_HEADERS_EXCEPTION_JOBEXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_JOBEXCEPTION_H_

#include <exception>
#include <string>

namespace std {

class JobException : public exception {
private:
	string message;
public:
	JobException(string message);

	virtual const char* what() const throw() {
		return message.c_str();
	};

	virtual ~JobException(){};
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_EXCEPTION_JOBEXCEPTION_H_ */
