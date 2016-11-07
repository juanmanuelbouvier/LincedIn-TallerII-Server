#include <model/Chat.h>
#include <utils/VectorUtils.h>
#include <services/Logger/Logger.h>

#define ID_SEPARATOR "_"

Chat::Chat( string chat_id ) {
	DBManager db("Chat");
	if ( db.open() ) {
		Json::Value chat = db.getJSON(chat_id);
		if ( !chat.isNull() ) {
			chatID = chat_id;
		}
	}

}

string Chat::generateID( list<string> participants ) {
	participants.sort();
	participants.unique();

	if ( participants.size() < 2 ) {
		Log(typeid(this).name() + "(" + __LINE__ + "). The chat must have two or more participantas",ERROR);
		throw InvalidChatParticipants("The participants");
	}

	vector<string> vectorToJoin( begin(participants), end(participants) );
	string id = VectorUtils::joinVector(vectorToJoin,ID_SEPARATOR);

	return id;
}


Chat::~Chat() {
	// TODO Auto-generated destructor stub
}

