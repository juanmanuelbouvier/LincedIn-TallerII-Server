#ifndef SRC_MAIN_HEADERS_EXCEPTION_JOBEXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_JOBEXCEPTION_H_

#include <exception/AppServerException.h>

using namespace std;

class JobException : public AppServerException {
public:
	JobException(string msg) : AppServerException(msg){};
	virtual ~JobException(){};
};

#endif /* SRC_MAIN_HEADERS_EXCEPTION_JOBEXCEPTION_H_ */
