#ifndef SRC_MAIN_SRC_MODEL_CHAT_H_
#define SRC_MAIN_SRC_MODEL_CHAT_H_

#include <string>
#include <list>
#include <extern/json.h>
#include <services/DB/DBManager.h>
#include <utils/ErrorMessage.h>

using namespace std;


class Chat {
	static DB* getDB();
	static DB* getChatsDB();

	string chatID;
	Json::Value participants;
	Json::Value messages;

	static string generateID( list<string> participants );
	static void setChatToUser( list<string> user_id, string chat_id );
	static bool deleteChatOfParticipant( Json::Value participants, string chat_id );

public:
	Chat( string id );

	static ErrorMessage check( list<string> participants_id );
	static Chat create( list<string> participants_id );
	static list<Chat> getChatsFromUser(string user_id);
	static bool isUserInChat( string user_id, string chat_id );
	static bool exist( string chat_id );
	static bool Delete( string chat_id );

	bool update(  );

	bool isMember(string user_id);

	bool addMessage( string user_id, string message );

	string getId();
	Json::Value getMessages();
	Json::Value getLastMessage();
	Json::Value getParticipants();
	Json::Value asJson();



	virtual ~Chat();
};

#endif /* SRC_MAIN_SRC_MODEL_CHAT_H_ */
