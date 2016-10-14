#include <SettingManagerTest.h>
#include <settings/SettingManager.h>
#include <services/Logger/Logger.h>
#include <utils/DateUtils.h>

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void SetUpSettingFile( string file, string name ) {
	ofstream out(name);
	out << file;
	out.close();
}

void SetUpDefaultFile(string name) {
	string fileSetting = "{\"logger\":{\"level\":1,\"file\":\"test.log\",\"show_in_stout\":false},\"port\":9191,\"shared_server_url\":\"jaja:1234\"}";
	SetUpSettingFile(fileSetting,name);
}

TEST(SettingManagerTest, readJsonSetting) {
	string fileSettingName = "setting.json";
	SetUpDefaultFile(fileSettingName);

	SettingManager* settings = SettingManager::getInstance();


	cout.setstate(std::ios_base::failbit);

	EXPECT_FALSE( settings->readFile("fakefile") );
	EXPECT_TRUE( settings->readFile(fileSettingName) );

	EXPECT_EQ(settings->getServerPort(), 9191);
	EXPECT_EQ(settings->getLogFile(), "test.log");
	EXPECT_EQ(settings->getLogLevel(), 1);
	EXPECT_FALSE(settings->showLoggerInStdout());

	EXPECT_EQ(settings->getSharedServerURL(), "jaja:1234");
	cout.clear();

	SettingManager::deleteInstance();

}

TEST(SettingManagerTest, DummyTestLogFromSetting){
	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	//Disbale STDOUT
	cout.setstate(std::ios_base::failbit);

	EXPECT_FALSE(settings->readFile("fakefile"));

	string text = Log("Not inizializ");

	EXPECT_EQ(text,"ERROR: Logger must be initialized with `LoggerInit(level,log_console,path)`");

	settings->initDefaultLogger();
	string alog = Log("Hello",WARNING);

	string expectedLog = DateUtils::getTimeWithFormat() + "[WARNING] Hello";

	EXPECT_EQ(alog,expectedLog);

	//Enable STDOUT
	cout.clear();
	SettingManager::deleteInstance();

}

TEST(SettingManagerTest, DummyTestForOtherMethod) {
	string filename = "setting.json";
	SetUpDefaultFile(filename);

	SettingManager* settings = SettingManager::getInstance();


	string msg = settings->getJSONStructure();
	EXPECT_TRUE( msg.size() > 0 );

	settings->readFile(filename);
	EXPECT_EQ( settings->getDirectValue("logger"), "" );
	SettingManager::deleteInstance();

}

TEST(SettingManagerTest, SettingsWithWrongValues) {
	//Wrong levele and worng port
	string settingFile = ""
			"{"
				"\"logger\":{"
					"\"level\":44,"
					"\"file\":\"fakepath/fakefile.log\","
					"\"show_in_stout\":\"fake\""
				"},"
				"\"port\":9191"
			"}";
	string settingFileName = "wrong.json";
	SetUpSettingFile(settingFile,settingFileName);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	//Disbale STDOUT
	cout.setstate(std::ios_base::failbit);

	EXPECT_EQ( settings->getLogFile(), "LincedInAppServer.log");
	EXPECT_FALSE(settings->readFile("fakefile"));

	EXPECT_EQ( settings->getServerPort(), 8081 );
	EXPECT_EQ( settings->getLogLevel(), 3);

	settings->readFile("wrong.json");
	EXPECT_EQ( settings->getLogLevel(), 3);
	EXPECT_TRUE(settings->showLoggerInStdout());
	EXPECT_EQ(settings->getSharedServerURL(), "lincedin.herokuapp.com:80");

	//Enable STDOUT
	cout.clear();

	SettingManager::deleteInstance();

}

TEST(SettingManagerTest, TestInitializeLogger) {
	cout.setstate(std::ios_base::failbit);

	string settingFileName = "setting.json";
	SetUpDefaultFile(settingFileName);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	settings->initDefaultLogger();
	string expectedLog = DateUtils::getTimeWithFormat() + "[DEBUG] HI";
	EXPECT_EQ(Log("HI",DEBUG),expectedLog);

	settings->readFile(settingFileName);

	settings->initLogger();

	EXPECT_EQ(Log("HI",DEBUG),"");

	//Enable STDOUT
	cout.clear();

	SettingManager::deleteInstance();
}

TEST(SettingManagerTest, WrongJSONFormat) {
	cout.setstate(std::ios_base::failbit);

	string wrong = "this is not a json file\n";
	string wrongName = "wrong2.json";
	SetUpSettingFile(wrong,wrongName);

	cout.setstate(std::ios_base::failbit);

	//SUPRESS JSON EXPECTED ERROR
	fclose(stderr);
	EXPECT_FALSE(SettingManager::getInstance()->readFile("wrong2.json"));

	cout.clear();
	SettingManager::deleteInstance();
}
