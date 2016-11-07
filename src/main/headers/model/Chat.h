#ifndef SRC_MAIN_SRC_MODEL_CHAT_H_
#define SRC_MAIN_SRC_MODEL_CHAT_H_

#include <string>
#include <list>

using namespace std;

class Chat {

	string chatID;
	list<string> participants_sorted;

	static string generateID( list<string> participants );

public:
	Chat( string id );

	static Chat check( list<string> participants_id );
	static Chat create( list<string> participants_id );

	bool addMessage( string user_id, string message );

	virtual ~Chat();
};

#endif /* SRC_MAIN_SRC_MODEL_CHAT_H_ */
