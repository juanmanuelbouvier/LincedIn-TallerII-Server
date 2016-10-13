#include <SettingManagerTest.h>
#include <settings/SettingManager.h>

#include <string>

using namespace std;

TEST(SettingManagerTest, readJsonSetting) {
	string file = "settings/setting.json";
	SettingManager* settings = SettingManager::getInstance();

	EXPECT_TRUE(settings->readFile(file));

	EXPECT_EQ(settings->getServerPort(), 8081);
	EXPECT_EQ(settings->getLogFile(), "logs/LincedInAppServer.log");
	EXPECT_EQ(settings->getLogLevel(), 3);
	EXPECT_FALSE(settings->showLoggerInStdout());



}

