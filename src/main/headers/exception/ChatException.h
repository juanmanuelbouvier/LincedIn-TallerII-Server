#ifndef SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_
#define SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_

#include <exception>
#include <string>

using namespace std;

class ChatException : public exception {

private:
	string message;

public:
	virtual const char* what() const throw() {
		return message.c_str();
	};

	ChatException( string message );

	virtual ~ChatException(){};
};

#endif /* SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_ */
