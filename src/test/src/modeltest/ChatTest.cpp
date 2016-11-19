#include <modeltest/ChatTest.h>
#include <extern/json.h>
#include <settings/SettingManager.h>
#include <model/Chat.h>
#include <utils/DateUtils.h>
#include <model/User.h>
#include <TestHelper.h>

using namespace std;

TEST(ChatTest, TestCreateChat) {
	TestHelper::settinUpTestModel();

	ASSERT_EQ( SettingManager::getInstance()->getDBFolder(), ".temp-test/" );

	string name1 = "cacho";
	string name2 = "pepo";

	User user1 = TestHelper::createBasicUsers(name1);
	User user2 = TestHelper::createBasicUsers(name2);

	list<string> participants = {user1.getID()};

	ASSERT_TRUE(Chat::check(participants));

	participants.push_back(user1.getID());
	ASSERT_TRUE(Chat::check(participants));

	participants.push_back(user2.getID());
	ASSERT_TRUE(Chat::check(participants));

	participants.pop_front();
	Chat chat = Chat::create(participants);

	EXPECT_EQ(chat.getId(), user1.getID() + "_" + user2.getID());

	EXPECT_EQ(chat.getMessages().size(), 0);

	Json::Value expectedParticipants;
	expectedParticipants.append(user1.getID());
	expectedParticipants.append(user2.getID());

	EXPECT_EQ( chat.getParticipants(), expectedParticipants);
	DBManager::deleteInstance();
}

TEST(ChatTest, TestChatSendMessage) {
	TestHelper::settinUpTestModel();

	string name1 = "cacho";
	string name2 = "pepo";

	list<string> participants = { name1, name2 };

	Chat chat(name1 + "_" + name2);
	ASSERT_FALSE(chat.addMessage("p8","Hi, p2"));

	EXPECT_TRUE(chat.addMessage(name1,"Hi, p2"));
	EXPECT_TRUE(chat.addMessage(name2,"Hi.."));

	EXPECT_EQ(chat.getMessages().size(), 2);

	DBManager::deleteInstance();
}


TEST(ChatTest, TestChatGetMessage) {
	//Depends on the above test
	TestHelper::settinUpTestModel();

	string name1 = "cacho";
	string name2 = "pepo";

	Chat chat(name1 + "_" + name2);
	Json::Value messages = chat.getMessages();
	EXPECT_EQ(messages.size(), 2);
	EXPECT_TRUE(messages.isArray());
	EXPECT_EQ(messages[0]["message"].asString(),"Hi, p2");
	EXPECT_EQ(messages[1]["message"].asString(),"Hi..");

	DBManager::deleteInstance();

}
