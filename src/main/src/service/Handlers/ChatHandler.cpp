#include <services/Handlers/ChatHandler.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <model/Chat.h>
#include <model/User.h>
#include <utils/JSONUtils.h>
#include <utils/TokenUtils.h>
#include <list>
#include <services/HTTP/HTTPResponseConstants.h>


static HTTPResponse* getChatFromUser(User user) {
	list<Chat> chats = Chat::getChatsFromUser(user.getID());
	Json::Value body;
	Json::Value chatsArray(Json::arrayValue);
	for (Chat& chat : chats) {
		Json::Value jsonChat;
		jsonChat["participants"] = chat.getParticipants();
		jsonChat["last_message"] = chat.getLastMessage();
		chatsArray.append(jsonChat);
	}
	return ResponseBuilder::createJsonResponse(CODE_OK,body);
}

static HTTPResponse* getOnlineFriendsFromUser(User user) {
	Json::Value general;
	general["info"] = "sooon";
	return ResponseBuilder::createJsonResponse(CODE_OK,general);
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
			return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"NO MESSAGE");
		}
		string message = body["message"].asString();
		if (chat.addMessage(user.getID(),message)){
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

HTTPResponse* ChatHandler::handle(HTTPRequest* http_request) {

	string token = http_request->getFromHeader("Authorization");
	if ( !TokenUtils::isValidToken(token) ) {
		return ResponseBuilder::createErrorResponse(CODE_PERMISSION_DENIED,PHRASE_PERMISSION_DENIED);
	}
	User user = TokenUtils::userByToken(token);

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat") && http_request->isGET()){
		return getChatFromUser(user);
	}

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat/online") && http_request->isGET()) {
		return getOnlineFriendsFromUser(user);
	}

	if (PathUtils::matchPathRegexp(http_request->getURI(),"/chat/:user_id")) {
		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/chat/:user_id");
		string chat_id = path["chat_id"];
		return handleChat(http_request,chat_id,user);
	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}


