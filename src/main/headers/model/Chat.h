#ifndef SRC_MAIN_SRC_MODEL_CHAT_H_
#define SRC_MAIN_SRC_MODEL_CHAT_H_

#include <string>
#include <list>
#include <extern/json.h>
#include <services/DB/DBManager.h>
#include <utils/ErrorMessage.h>

using namespace std;

/**
 * A chat if a object who used to comunicate two ore more users.
 */
class Chat {
	static DB* getDB();
	static DB* getChatsDB();

	string chatID;
	Json::Value participants;
	Json::Value messages;

	/**
	 * Generate private and unique id of a chat.
	 * @param List of participants
	 * @return chat id
	 */
	static string generateID( list<string> participants );

	static void setChatToUser( list<string> user_id, string chat_id );
	static bool deleteChatOfParticipant( Json::Value participants, string chat_id );

	/**
	 * Update Chat attributes in Database
	 * @return True if it was successful.
	 */
	bool update();

public:
	/**
	 * Get a Chat from DB
	 * @param id of chat
	 * @note If id not exist, throw an exception
	 */
	Chat( string id );

	/**
	 * Check if a list of participant can create a chat.
	 * @param List of participants id
	 * @return ErrorMessage who contains error, if exist.
	 */
	static ErrorMessage check( list<string> participants_id );

	/**
	 * Create Chat with the participants
	 * @param list of participants id.
	 * @return Chat who be created.
	 * @note. If chat already exist. Return de exist chat
	 */
	static Chat create( list<string> participants_id );

	/**
	 * Get list of chat who the user is a participant.
	 * @param user id.
	 * @return List ff chats of the user.
	 */
	static list<Chat> getChatsFromUser(string user_id);

	/**
	 * Check if user id is in chat id
	 * @param user id.
	 * @param chat id
	 * @return true if user in chat.
	 */
	static bool isUserInChat( string user_id, string chat_id );

	/**
	 * Check if chat Id exist
	 * @param chat id.
	 * @return true if chat exist.
	 */
	static bool exist( string chat_id );

	/**
	 * Delete chat in db
	 * @param chat_id to be deleted
	 * @return True if was succesfully deleted
	 */
	static bool Delete( string chat_id );

	/**
	 * Check if user_id if member of Chat
	 * @param user id
	 * @return True if User id is in chat
	 */
	bool isMember(string user_id);

	/**
	 * Add Message from user
	 * @param user_id, message
	 * @return True if the message added succesfully
	 */
	bool addMessage( string user_id, string message );

	string getId();
	Json::Value getMessages();
	Json::Value getLastMessage();
	Json::Value getParticipants();

	/**
	 * Get the message data as JSON
	 * @return All chat information in Json::Value
	 * @note the json is: { participants : [..], messages: [ { user_id, message, timestamp} ] }
	 */
	Json::Value asJson();

	virtual ~Chat();
};

#endif /* SRC_MAIN_SRC_MODEL_CHAT_H_ */
