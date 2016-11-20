#include <modeltest/ChatTest.h>
#include <extern/json.h>
#include <settings/SettingManager.h>
#include <model/Chat.h>
#include <utils/DateUtils.h>
#include <model/User.h>
#include <TestHelper.h>
#include <vector>
#include <exception/ChatException.h>

using namespace std;

#define USER1 "chat_cacho"
#define USER2 "chat_pepo"
#define USER3 "chat_raul"

TEST(ChatTest, TestCreateChat) {
	TestHelper::settinUpTestModel();

	string name1 = USER1;
	string name2 = USER2;

	User user1 = TestHelper::createBasicUsers(name1);
	User user2 = TestHelper::createBasicUsers(name2);

	list<string> participants = {user1.getID()};

	EXPECT_TRUE(Chat::check(participants));

	participants.push_back(user1.getID());
	EXPECT_TRUE(Chat::check(participants));

	participants.push_back(user2.getID());
	EXPECT_TRUE(Chat::check(participants));

	EXPECT_THROW(Chat::create(participants), ChatException);

	participants.pop_front();

	participants.push_back("invalid");
	EXPECT_TRUE(Chat::check(participants));
	participants.pop_back();

	Chat chat = Chat::create(participants);

	EXPECT_TRUE(Chat::check(participants));

	EXPECT_EQ(chat.getId(), user1.getID() + "_" + user2.getID());

	EXPECT_EQ(chat.getMessages().size(), 0);

	Json::Value expectedParticipants;
	expectedParticipants.append(user1.getID());
	expectedParticipants.append(user2.getID());

	EXPECT_EQ( chat.getParticipants(), expectedParticipants);


	EXPECT_THROW(Chat("invalid"), ChatException);
}

TEST(ChatTest, TestChatSendMessage) {
	TestHelper::settinUpTestModel();

	string name1 = USER1;
	string name2 = USER2;

	list<string> participants = { name1, name2 };

	Chat chat(name1 + "_" + name2);
	EXPECT_FALSE(chat.addMessage("p8","Hi, p2"));

	EXPECT_TRUE(chat.addMessage(name1,"Hi, p2"));
	EXPECT_TRUE(chat.addMessage(name2,"Hi.."));

	EXPECT_EQ(chat.getMessages().size(), 2);

}


TEST(ChatTest, TestChatGetMessage) {
	//Depends on the above test
	TestHelper::settinUpTestModel();

	string name1 = USER1;
	string name2 = USER2;

	Chat chat(name1 + "_" + name2);
	Json::Value messages = chat.getMessages();
	EXPECT_EQ(messages.size(), 2);
	EXPECT_TRUE(messages.isArray());
	EXPECT_EQ(messages[0]["message"].asString(),"Hi, p2");
	EXPECT_EQ(messages[1]["message"].asString(),"Hi..");

}

TEST(ChatTest, ChatWithThree) {
	//Depends on the above test
	TestHelper::settinUpTestModel();

	string name1 = USER1;
	string name2 = USER2;
	string name3 = USER3;
	User user3 = TestHelper::createBasicUsers(name3);

	list<string> participants = {name1,name2,name3};
	ErrorMessage error = Chat::check(participants);
	EXPECT_FALSE(error);

	Chat created = Chat::create(participants);
	string id = name1 + "_" + name2 + "_" + name3;
	EXPECT_TRUE(Chat::exist(id));
	Chat chat(id);

	chat.getParticipants();
	EXPECT_EQ(chat.getParticipants().size(),3);
	EXPECT_TRUE( chat.getLastMessage().isNull() );

	EXPECT_TRUE(chat.isMember(name1));
	EXPECT_TRUE(chat.isMember(name2));
	EXPECT_TRUE(chat.isMember(name3));
	EXPECT_FALSE(chat.isMember("name4"));

	chat.addMessage(name3,"Hi kids");
	chat.addMessage(name2,"Hiiiiiii");
	chat.addMessage(name2,"Hiiiiiii again");
	chat.addMessage(name1,"bye");

	Chat sameChat(id);
	Json::Value lastMessage = sameChat.getLastMessage();
	EXPECT_EQ(lastMessage["message"].asString(), "bye");
	EXPECT_EQ(lastMessage["user_id"].asString(), name1);

	Json::Value jsonSameChat = chat.asJson();
	Json::Value message = jsonSameChat["messages"];
	EXPECT_EQ(message.size(), 4);
	EXPECT_EQ(message[0]["message"].asString(),"Hi kids");

}


TEST(ChatTest, getChats) {
	//Depends on the above test
	TestHelper::settinUpTestModel();

	string name1 = USER1;
	string name2 = USER2;
	string name3 = USER3;

	string chat_1 = name1 + "_" + name2;
	string chat_2 = name1 + "_" + name2 + "_" + name3;
	EXPECT_TRUE(Chat::isUserInChat(name1,chat_1));
	EXPECT_TRUE(Chat::isUserInChat(name2,chat_1));
	EXPECT_FALSE(Chat::isUserInChat(name3,chat_1));

	EXPECT_TRUE(Chat::isUserInChat(name1,chat_2));
	EXPECT_TRUE(Chat::isUserInChat(name2,chat_2));
	EXPECT_TRUE(Chat::isUserInChat(name3,chat_2));

	list<Chat> chats_user1 = Chat::getChatsFromUser(name1);
	ASSERT_EQ(chats_user1.size(),2);
	for (Chat& c : chats_user1) {
		ASSERT_TRUE( c.getId() == chat_1 || c.getId() == chat_2 );
	}

	list<Chat> chats_user3 = Chat::getChatsFromUser(name3);
	ASSERT_EQ(chats_user3.size(),1);
	vector<Chat> chats3;
	for (Chat& c3 : chats_user3) {
		chats3.push_back(c3);
	}
	Chat c2 = chats3[0];
	ASSERT_EQ(c2.getId(),chat_2);

	ASSERT_EQ(Chat::getChatsFromUser("invalid").size(),0);
}

TEST(ChatTest, deleteChat) {
	//Depends on the above test
	TestHelper::settinUpTestModel();

	string name1 = USER1;
	string name2 = USER2;
	string name3 = USER3;

	string chat_1 = name1 + "_" + name2;
	string chat_2 = name1 + "_" + name2 + "_" + name3;

	EXPECT_TRUE(Chat::isUserInChat(name1,chat_1));
	Chat::Delete(chat_1);
	EXPECT_FALSE(Chat::isUserInChat(name1,chat_1));

	list<Chat> chats_user1 = Chat::getChatsFromUser(name1);
	ASSERT_EQ(chats_user1.size(),1);
	EXPECT_TRUE(Chat::isUserInChat(name1,chat_2));

}
