#include <exception/ChatException.h>
#include <model/Chat.h>
#include <utils/VectorUtils.h>
#include <services/Logger/Logger.h>
#include <utils/JSONUtils.h>
#include <utils/DateUtils.h>

#include <iostream>

#define ID_SEPARATOR "_"
#define CHAT_DB "Chat"

DBManager* Chat::chatDB = NULL;

DBManager* Chat::getDB(){
	if (!chatDB) {
		chatDB = new DBManager(CHAT_DB);
		if (chatDB->open()){
			return chatDB;
		} else {
			cout << Log("Chat.cpp::" + to_string(__LINE__) + ". Can't open " + string(CHAT_DB) + " DB",WARNING) << endl;
			throw new ChatException("Can't open Chat DB");
		}
	}
	return chatDB;
}

Chat::Chat( string chat_id ) {
	Json::Value chat = getDB()->getJSON(chat_id);
	if ( !chat.isNull() ) {
		chatID = chat_id;
		messages = chat["messages"];
		participants = chat["participants"];
	}
	//DONT EXIST
}

Chat Chat::create( list<string> participants_id ) {
	string message = "Invalid participants";
	if (check(participants_id)) {
		string id = generateID(participants_id);

		Json::Value chat;
		chat["participants"] = JSONUtils::listToArrayValue(participants_id);
		chat["messages"] = Json::arrayValue;
		chat["total"] = 0;
		message = "Cannot Store in chatDB";
		if ( getDB()->storeJSON(id,chat) ) {
			return Chat(id);
		}
	}
	throw new ChatException(message);
}

bool Chat::check( list<string> participants ) {
	size_t size = participants.size();
	participants.unique();
	if ( participants.size() < 2 || participants.size() != size ) {
		Log("Chat.cpp::" + to_string(__LINE__) + ". The chat must have two or more disctinct participantas",ERROR);
		return false;
	}

	/*
	for ( const string& user_id : participants ) {
		if (!User::exist(user_id)) {
			Log("Chat" + " (" + __LINE__ + "). User id: " + user_id + " does not exist",ERROR);
			errors["user" + user_id] = "User id: " + user_id + " does not exist";
		}
	}
	*/
	return true;

}

bool Chat::update() {
	Json::Value chatDB;
	chatDB["participants"] = participants;
	chatDB["messages"] = messages;
	chatDB["total"] = messages.size();
	return getDB()->storeJSON(chatID, chatDB);

	Log("Chat.cpp::" + to_string(__LINE__) + ". Cannot update Chat in DB, can't open Chat DB",WARNING);
	return false;
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

Chat::~Chat() {
	// TODO Auto-generated destructor stub
}

