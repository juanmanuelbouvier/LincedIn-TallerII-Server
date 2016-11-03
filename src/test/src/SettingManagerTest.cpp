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
	string fileSetting = ""
			"{"
				"\"logger\":{"
					"\"level\":1,"
					"\"file\":\"test.log\","
					"\"show_in_stout\":false"
				"},"
				"\"port\":9191,"
				"\"shared_server_url\":\"jaja:1234\","
				"\"db_folder\":\".temp-test/folderToDB\""
			"}";
	SetUpSettingFile(fileSetting,name);
}

TEST(SettingManagerTest, readJsonSetting) {
	string fileSettingName = ".temp-test/setting.json";
	SetUpDefaultFile(fileSettingName);

	SettingManager* settings = SettingManager::getInstance();

	//Disable cout message
	cout.setstate(std::ios_base::failbit);

	EXPECT_FALSE( settings->readFile("fakefile") );
	EXPECT_TRUE( settings->readFile(fileSettingName) );

	EXPECT_EQ(settings->getServerPort(), 9191);
	EXPECT_EQ(settings->getLogFile(), "test.log");
	EXPECT_EQ(settings->getLogLevel(), 1);
	EXPECT_FALSE(settings->showLoggerInStdout());

	EXPECT_EQ(settings->getSharedServerURL(), "jaja:1234");

	//Enable cout
	cout.clear();

	SettingManager::deleteInstance();

}

TEST(SettingManagerTest, DummyTestLogFromSetting){
	//Disbale STDOUT
	cout.setstate(std::ios_base::failbit);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	EXPECT_FALSE(settings->readFile("fakefile"));

	string text = Log("Not inizialize",INFO);
	EXPECT_EQ(text,"ERROR: Logger must be initialized with `LoggerInit(level,log_console,path)`");

	settings->initDefaultLogger();

	string alog = Log("Hello",WARNING);
	string expectedLog = DateUtils::getTimeWithFormat() + "[WARNING] Hello";
	EXPECT_EQ(alog,expectedLog);

	SettingManager::deleteInstance();

	//Enable STDOUT
	cout.clear();

}

TEST(SettingManagerTest, DummyTestForOtherMethod) {
	string filename = ".temp-test/setting.json";
	SetUpDefaultFile(filename);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	string msg = settings->getJSONStructure();
	EXPECT_TRUE( msg.size() > 0 );

	settings->readFile(filename);
	EXPECT_EQ( settings->getDirectValue("logger"), "" );

	SettingManager::deleteInstance();

}

TEST(SettingManagerTest, SettingsWithWrongValues) {
	//Disbale STDOUT
	cout.setstate(std::ios_base::failbit);

	//Wrong levele and worng port
	string settingFileName = ".temp-test/wrong.json";
	string settingFile = ""
			"{"
				"\"logger\":{"
					"\"level\":44,"
					"\"file\":\"fakepath/fakefile.log\","
					"\"show_in_stout\":\"fake\""
				"},"
				"\"port\":9191"
			"}";
	SetUpSettingFile(settingFile,settingFileName);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	EXPECT_EQ( settings->getLogFile(), "LincedInAppServer.log");
	EXPECT_FALSE(settings->readFile("fakefile"));

	EXPECT_EQ( settings->getServerPort(), 8081 );
	EXPECT_EQ( settings->getLogLevel(), 3);

	settings->readFile(settingFileName);
	EXPECT_EQ( settings->getLogLevel(), 3);
	EXPECT_TRUE(settings->showLoggerInStdout());
	EXPECT_EQ(settings->getSharedServerURL(), "lincedin.herokuapp.com:80");

	SettingManager::deleteInstance();

	//Enable STDOUT
	cout.clear();

}

TEST(SettingManagerTest, TestInitializeLogger) {
	//Disable STDOUT
	cout.setstate(std::ios_base::failbit);

	string settingFileName = ".temp-test/setting.json";
	SetUpDefaultFile(settingFileName);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();

	settings->initDefaultLogger();
	string expectedLog = DateUtils::getTimeWithFormat() + "[DEBUG] HI";
	EXPECT_EQ(Log("HI",DEBUG),expectedLog);


	settings->readFile(settingFileName);

	//Not log because loglevel in settingFileName is 1 = WARNING
	settings->initLogger();
	EXPECT_EQ(Log("HI",DEBUG),"");

	SettingManager::deleteInstance();

	//Enable STDOUT
	cout.clear();
}

TEST(SettingManagerTest, WrongJSONFormat) {
	//Disbale cout for stdout and stderr
	cout.setstate(std::ios_base::failbit);
	fclose(stderr);

	string wrong = "this is not a json file\n";
	string wrongName = ".temp-test/wrong2.json";
	SetUpSettingFile(wrong,wrongName);

	EXPECT_FALSE( SettingManager::getInstance()->readFile(wrongName) );

	cout.clear();
	SettingManager::deleteInstance();
}


TEST(SettingManagerTest, DBFolder) {
	cout.setstate(std::ios_base::failbit);
	fclose(stderr);

	string jsonSetting = ".temp-test/example.json";
	SetUpDefaultFile(jsonSetting);

	SettingManager::deleteInstance();
	SettingManager* settings = SettingManager::getInstance();
	settings->readFile(jsonSetting);

	EXPECT_EQ(settings->getDBFolder(),"db");

	mkdir(".temp-test/folderToDB", ACCESSPERMS);
	settings->readFile(jsonSetting);
	EXPECT_EQ(settings->getDBFolder(),".temp-test/folderToDB");

	cout.clear();
}
