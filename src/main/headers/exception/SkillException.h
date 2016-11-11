#ifndef SRC_MAIN_HEADERS_EXCEPTION_SKILLEXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_SKILLEXCEPTION_H_

#include <string>
#include <exception>

namespace std {

class SkillException : public exception {
private:
	string message;
public:

	virtual const char* what() const throw() {
		return message.c_str();
	};
	string getMenssage(){
		return message;
	}
	SkillException(string message);
	virtual ~SkillException(){};
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_EXCEPTION_SKILLEXCEPTION_H_ */
