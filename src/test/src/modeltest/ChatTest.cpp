#include <modeltest/ChatTest.h>
#include <fstream>
#include <string>
#include <iostream>
#include <extern/json.h>
#include <settings/SettingManager.h>
#include <model/Chat.h>
#include <utils/DateUtils.h>

using namespace std;

void settinUpDBFolderForModel() {
	string json = "{\"db_folder\" : \".temp-test/\"}\n";

	ofstream out(".temp-test/setting-model.json");
	out << json;
	out.close();

	SettingManager::getInstance()->readFile(".temp-test/setting-model.json");
}

TEST(ChatTest, TestCreateChat) {
	settinUpDBFolderForModel();

	ASSERT_EQ( SettingManager::getInstance()->getDBFolder(), ".temp-test/" );

	list<string> participants = {"macri"};

	ASSERT_FALSE(Chat::check(participants));

	participants.push_back("macri");
	ASSERT_FALSE(Chat::check(participants));


	participants.push_back("cfk");
	ASSERT_FALSE(Chat::check(participants));

	participants.pop_front();
	Chat chat = Chat::create(participants);

	EXPECT_EQ(chat.getId(), "cfk_macri");

	EXPECT_EQ(chat.getMessages().size(), 0);

	Json::Value expectedParticipants;
	expectedParticipants.append("macri");
	expectedParticipants.append("cfk");

	EXPECT_EQ( chat.getParticipants(), expectedParticipants);
}

TEST(ChatTest, TestChatSendMessage) {
	settinUpDBFolderForModel();
	list<string> participants = { "p1", "p2" };

	Chat chat = Chat::create(participants);

	ASSERT_FALSE(chat.addMessage("p8","Hi, p2"));

	EXPECT_TRUE(chat.addMessage("p1","Hi, p2"));
	EXPECT_TRUE(chat.addMessage("p2","Hi.."));

	EXPECT_EQ(chat.getMessages().size(), 2);
}


TEST(ChatTest, TestChatGetMessage) {
	//Depends on the above test
	settinUpDBFolderForModel();
	Chat chat("p1_p2");
	Json::Value messages = chat.getMessages();
	EXPECT_EQ(messages.size(), 2);
	EXPECT_TRUE(messages.isArray());
	EXPECT_EQ(messages[0]["message"].asString(),"Hi, p2");
	EXPECT_EQ(messages[1]["message"].asString(),"Hi..");

}
