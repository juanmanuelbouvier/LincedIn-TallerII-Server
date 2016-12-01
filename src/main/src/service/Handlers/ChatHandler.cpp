#include <services/Handlers/ChatHandler.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <model/Chat.h>
#include <model/User.h>
#include <model/Friends.h>
#include <utils/JSONUtils.h>
#include <utils/TokenUtils.h>
#include <list>
#include <services/HTTP/HTTPResponseConstants.h>
#include <services/Firebase/FirebaseClient.h>

static HTTPResponse* getChatFromUser(User user) {
	list<Chat> chats = Chat::getChatsFromUser(user.getID());
	Json::Value body;
	Json::Value chatsArray(Json::arrayValue);
	for (Chat& chat : chats) {
		Json::Value jsonChat;
		jsonChat["chat_id"] = chat.getId();
		jsonChat["participants"] = chat.getParticipants();
		jsonChat["last_message"] = chat.getLastMessage();
		chatsArray.append(jsonChat);
	}

	body["chats"] = chatsArray;

	return ResponseBuilder::createJsonResponse(CODE_OK,body);
}

static HTTPResponse* getOnlineFriendsFromUser(User user) {

	Json::Value general;
	general["friends_online"] = Friends::listFriendsOnline(user.getID());
	return ResponseBuilder::createJsonResponse(CODE_OK,general);

}

void sendFirebaseNotification(Chat chat,User user_source,string message){
	string fullName = user_source.getFullName();
	string id = user_source.getID();
	Json::Value participants = chat.getParticipants();

	for (auto itr : participants) {
	    string user_destination_id = itr.asString();
	    if (user_destination_id == id)
	    	continue;
	    string firebase_id = User::getFirebaseID(user_destination_id);
		FirebaseClient::sendNotifications(firebase_id,"Nuevo mensaje de " + fullName,fullName + ": " + message);
	}
}

static HTTPResponse* handleChat(HTTPRequest* request,string chat_id, User user) {
	if (!Chat::exist(chat_id)) {
		return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"Chat");
	}
	Chat chat(chat_id);

	if (request->isGET()) {
		return ResponseBuilder::createJsonResponse(CODE_OK,chat.asJson());
	}

	if ( request->isPOST() ) {
		Json::Value body = JSONUtils::stringToJSON(request->getBody());
		if (!body.isMember("message") || !body["message"].isString() || body["message"].asString().empty()) {
			return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"NO MESSAGE");
		}
		string message = body["message"].asString();
		if (chat.addMessage(user.getID(),message)){
			sendFirebaseNotification(chat,user,message);
			return ResponseBuilder::createJsonResponse(CODE_OK,chat.getLastMessage());
		}
		ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR,"INTERNAL ERROR");
	}

	if ( request->isDELETE() ){
		if ( Chat::Delete(chat.getId()) ) {
			return ResponseBuilder::createEmptyResponse(204,"Chat deleted");
		}
		return ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR,"INTERNAL ERROR");
	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}

HTTPResponse* createChatFromUser(User user, Json::Value data) {
	if (data.isMember("participants") && data["participants"].isArray() ) {
		list<string> participants;
		participants.push_back(user.getID());
		for (auto p : data["participants"]) {
			participants.push_back(p.asString());
		}
		ErrorMessage error = Chat::check(participants);
		if (!error) {
			Chat chat = Chat::create(participants);
			Json::Value body;
			body["chat_id"] = chat.getId();
			return ResponseBuilder::createJsonResponse(CODE_OK,body);
		}
		return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,error.summary());
	}
	return ResponseBuilder::createErrorResponse(CODE_BREACH_PRECONDITIONS,"Not defined Participants in body");


}

HTTPResponse* ChatHandler::handle(HTTPRequest* http_request) {

	string token = http_request->getFromHeader("Authorization");
	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
	}
	User user = TokenUtils::userByToken(token);

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat")){
		if (http_request->isGET()) {
			return getChatFromUser(user);
		} else if (http_request->isPOST()) {
			Json::Value data = JSONUtils::stringToJSON(http_request->getBody());
			return createChatFromUser(user,data);
		}
	}

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat/online") && http_request->isGET()) {
		return getOnlineFriendsFromUser(user);
	}

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat/:chat_id")) {
		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/chat/:chat_id");
		string chat_id = path["chat_id"];
		return handleChat(http_request,chat_id,user);
	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}


