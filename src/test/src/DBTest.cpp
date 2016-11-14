#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <settings/SettingManager.h>
#include <gtest/gtest.h>
#include <services/DB/DB.h>

using namespace std;

void CreateFile( string file, string name ) {
	ofstream out(name);
	out << file;
	out.close();
}

TEST(DBTest, storeValue) {
	string file = "{\"db_folder\":\".temp-test/\"}";
	string filename = ".temp-test/testdb.json";

	CreateFile(file,filename);

	SettingManager* setting = SettingManager::getInstance();
	setting->readFile(filename);

	DB db("test");
	EXPECT_TRUE(db.open());
	EXPECT_TRUE(db.store("hello","world"));

	EXPECT_EQ(db.get("hello"),"world");

	SettingManager::deleteInstance();

}


TEST(DBTest, storeJson) {
	string file = "{\"db_folder\":\".temp-test/\"}";
	string filename = ".temp-test/testdb.json";

	CreateFile(file,filename);

	SettingManager* setting = SettingManager::getInstance();
	setting->readFile(filename);

	DB db("test");
	EXPECT_TRUE(db.open());

	Json::Value json;
	json["hello"] = "world";
	json["hello2"] = "world2";
	EXPECT_TRUE(db.storeJSON("a",json));

	Json::Value result = db.getJSON("a");
	EXPECT_EQ(result["hello"] ,"world");
	EXPECT_EQ(result["hello2"],"world2");

	Json::Value expectedEmpty;
	EXPECT_TRUE(db.getJSON("b").isMember("error"));

	SettingManager::deleteInstance();

}

TEST(DBTest, wrongUseOfDB) {
	string file = "{\"db_folder\":\".temp-test/\"}";
	string filename = ".temp-test/testdb.json";

	CreateFile(file,filename);

	SettingManager* setting = SettingManager::getInstance();
	setting->readFile(filename);

	//Invalid name
	DB db("someDB");

	//Before open
	EXPECT_FALSE(db.store("key","value"));
	EXPECT_EQ(db.get("key") ,"");

	EXPECT_TRUE(db.open());
	EXPECT_FALSE(db.open());

	SettingManager::deleteInstance();

}
