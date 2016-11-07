#ifndef SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_
#define SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_

#include <exception>

class InvalidChatParticipants : public std::runtime_error {
private:
	std::string message;
public:
	virtual const char* what() const throw() {
		return message.c_str();
	};

	InvalidChatParticipants( std::string message  );

	virtual ~InvalidChatParticipants(){};
};

#endif /* SRC_MAIN_SRC_EXCEPTION_INVALIDCHATPARTICIPANTS_H_ */
