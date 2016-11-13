#ifndef SRC_MAIN_HEADERS_EXCEPTION_SKILLEXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_SKILLEXCEPTION_H_

#include <exception/AppServerException.h>

using namespace std;

class SkillException : public AppServerException {
public:
	SkillException(string msg) : AppServerException(msg){};
	virtual ~SkillException(){};
};

#endif /* SRC_MAIN_HEADERS_EXCEPTION_SKILLEXCEPTION_H_ */
