#include <exception/ChatException.h>
#include <model/Chat.h>
#include <model/User.h>
#include <utils/VectorUtils.h>
#include <services/Logger/Logger.h>
#include <utils/JSONUtils.h>
#include <utils/DateUtils.h>

#define ID_SEPARATOR "_"
#define CHAT_DB "Chat"
#define CHATS_DB "Chats"

DB* Chat::getDB(){
	return DBManager::getDB(CHAT_DB);
}

DB* Chat::getChatsDB(){
	return DBManager::getDB(CHATS_DB);
}

Chat::Chat( string chat_id ) {
	if ( !getDB()->exist(chat_id) ) {
		throw ChatException ( Log("Chat.cpp::"+ to_string(__LINE__) +". Chat (" + chat_id + ") Can not be created because it doesn't exist in the database",ERROR) );
	}
	Json::Value chat = getDB()->getJSON(chat_id);
	chatID = chat_id;
	messages = chat["messages"];
	participants = chat["participants"];
}

list<Chat> Chat::getChatsFromUser(string user_id) {
	list<Chat> chats;
	if ( User::exist(user_id) && getChatsDB()->exist(user_id)) {
		Json::Value chats_user = getChatsDB()->getJSON(user_id);
		for (int i = 0; i < chats_user["chats"].size(); i++) {
			string chat_id = chats_user["chats"][i].asString();
			Chat chat( chat_id );
			chats.push_back( chat );
		}
	}
	return chats;
}

bool Chat::isUserInChat( string user_id, string chat_id ) {
	bool found = false;
	if ( getChatsDB()->exist(user_id) ) {
		Json::Value chats = getChatsDB()->getJSON(user_id);
		found = ( JSONUtils::isValueInArray(chat_id, chats["chats"]) != -1 );
	}
	return found;
}

void Chat::setChatToUser( list<string> users_id, string chat_id ) {
	for (string& user_id : users_id) {
		Json::Value chats;
		if ( getChatsDB()->exist(user_id) ) {
			chats = getChatsDB()->getJSON(user_id);
			chats["chats"].append(chat_id);
			chats["total"] = chats["chats"].size();
		} else {
			Json::Value chats_id(Json::arrayValue);
			chats_id.append(chat_id);
			chats["chats"] = chats_id;
			chats["total"] = 1;
		}
		if ( !getChatsDB()->storeJSON(user_id, chats) ) {
			throw ChatException( Log("Chat.cpp::"+ to_string(__LINE__) +". Cannot set chat to user_id: " + user_id, ERROR) );
		}
	}
}

Chat Chat::create( list<string> participants_id ) {
	ErrorMessage errors = check(participants_id);
	if (errors) {
		Log("Chat.cpp::"+ to_string(__LINE__) +". Cannot create chat. Data is invalid.\n Errors: " + errors.summary());
		throw ChatException(errors.summary());
	}

	string chatId = generateID(participants_id);
	Json::Value chat;
	chat["participants"] = JSONUtils::listToArrayValue(participants_id);
	chat["messages"] = Json::arrayValue;
	chat["total"] = 0;
	setChatToUser( participants_id, chatId );
	return ( getDB()->storeJSON(chatId,chat) ) ? Chat(chatId) : throw ChatException( Log("Cannot create chat with id: " + chatId,WARNING) );

}

ErrorMessage Chat::check( list<string> participants ) {
	ErrorMessage error;
	size_t size = participants.size();
	participants.unique();
	if ( participants.size() < 2 || participants.size() != size ) {
		error.addError("participants","The chat must have two or more disctinct participantas");;
	}

	string posibleChatId = generateID(participants);
	if ( exist(posibleChatId) ) {
		error.addError("id","Chat id " + posibleChatId + " already exist");
	}

	for ( const string& user_id : participants ) {
		if (!User::exist(user_id)) {
			error.addError(user_id,user_id + " does not exist.");
		}
	}

	return error;

}

bool Chat::exist( string chat_id ) {
	return ( getDB()->exist(chat_id) );
}

bool Chat::update() {
	Json::Value chatDB;
	chatDB["participants"] = participants;
	chatDB["messages"] = messages;
	chatDB["total"] = messages.size();
	return getDB()->storeJSON(chatID, chatDB);
}

string Chat::generateID( list<string> participants ) {
	participants.sort();
	vector<string> vectorToJoin( begin(participants), end(participants) );
	string id = VectorUtils::joinVector(vectorToJoin,ID_SEPARATOR);

	return id;
}

string Chat::getId() {
	return chatID;
}

Json::Value Chat::getMessages() {
	return messages;
}

Json::Value Chat::getLastMessage() {
	if (messages.size() > 0) {
		return messages[ messages.size() - 1 ];
	}
	return Json::Value(Json::nullValue);
}

Json::Value Chat::asJson() {
	Json::Value chat;
	chat["participants"] = participants;
	chat["messages"] = messages;
	return chat;
}

Json::Value Chat::getParticipants() {
	return participants;
}

bool Chat::isMember( string user_id ) {
	return (JSONUtils::isValueInArray(user_id, participants) != -1);
}

bool Chat::addMessage(string user_id, string message) {
	if ( isMember(user_id) ) {
		Json::Value messageValue;
		messageValue["user_id"] = user_id;
		messageValue["timestamp"] = DateUtils::getTimeWithFormat("%s");
		messageValue["message"] = message;
		messages.append( messageValue );
		return update();
	}
	Log("Chat.cpp::" + to_string(__LINE__) + ". The user_id " + user_id + " must be member of chat " + chatID + " to send message",WARNING);
	return false;
}


bool Chat::deleteChatOfParticipant( Json::Value participants, string chat_id ) {
	bool checkRemove = true;
	bool checkStore = true;
	for (int i = 0; i < participants.size() && checkRemove && checkStore; i++) {
		string user_id = participants[i].asString();
		if (getChatsDB()->exist(user_id)) {
			Json::Value participantData = getChatsDB()->getJSON(user_id);
			Json::Value chats_id = participantData["chats"];
			int position = JSONUtils::isValueInArray(chat_id,chats_id);
			Json::Value removedValue;
			checkRemove = chats_id.removeIndex( position, &removedValue);
			if ( checkRemove ) {
				participantData["chats"] = chats_id;
				participantData["total"] = chats_id.size();
				checkStore = getChatsDB()->storeJSON(user_id,participantData);
			}
			//Log("Chat.cpp::"+ to_string(__LINE__) +". Cannot delete chat (" + chat_id + ") on user (" + user_id + ").\n" + participantData.toStyledString(),ERROR);
		}
	}
	return true;
}

bool Chat::Delete(string chat_id) {
	bool ok = false;
	if ( getDB()->exist(chat_id) ) {
		Chat chat(chat_id);
		if (getDB()->Delete(chat_id)) {
			Json::Value participants = chat.getParticipants();
			ok = deleteChatOfParticipant(participants, chat_id);
		}
	}
	return ok;
}

Chat::~Chat() {
}

