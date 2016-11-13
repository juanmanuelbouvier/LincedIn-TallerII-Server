#ifndef SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_
#define SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_

#include <exception/AppServerException.h>

using namespace std;

class ChatException : public AppServerException {
public:
	ChatException(string msg) : AppServerException(msg){};
	virtual ~ChatException(){};
};

#endif /* SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_ */
