#ifndef SRC_MAIN_SRC_MODEL_CHAT_H_
#define SRC_MAIN_SRC_MODEL_CHAT_H_

#include <string>
#include <list>
#include <extern/json.h>
#include <services/DB/DBManager.h>

using namespace std;


class Chat {
	static DB* getDB();

	string chatID;
	Json::Value participants;
	Json::Value messages;

	static string generateID( list<string> participants );

public:
	Chat( string id );

	static bool check( list<string> participants_id );
	static Chat create( list<string> participants_id );

	bool update(  );

	bool isMember(string user_id);

	bool addMessage( string user_id, string message );

	string getId();
	Json::Value getMessages();
	Json::Value getLastMessage();
	Json::Value getParticipants();

	virtual ~Chat();
};

#endif /* SRC_MAIN_SRC_MODEL_CHAT_H_ */
