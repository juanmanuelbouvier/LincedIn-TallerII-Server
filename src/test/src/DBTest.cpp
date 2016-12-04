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

	EXPECT_TRUE(db.store("key2","{value205:245"));
	Json::Value result2 = db.getJSON("key2");
	EXPECT_TRUE(result2.isMember("error"));

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

TEST(DBTest, higgerKey) {
	string file = "{\"db_folder\":\".temp-test/\"}";
	string filename = ".temp-test/testdb.json";

	CreateFile(file,filename);

	SettingManager* setting = SettingManager::getInstance();
	setting->readFile(filename);

	DB db("higger");
	Json::Value data = db.getHigherKeyValue(5);
	EXPECT_TRUE(data.isMember("error"));
	EXPECT_FALSE(db.Delete("A"));

	db.open();
	db.store("A","{\"1\":\"1\"}");
	db.store("B","{\"4\":\"4\"}");
	db.store("C","{\"5\":\"5\"}");
	db.store("D","{\"3\":\"3\"}");
	db.store("E","{\"2\":\"2\"}");
	Json::Value data1 = db.getHigherKeyValue(0);
	EXPECT_EQ(data1["2"],"2");

	Json::Value data2 = db.getHigherKeyValue(1);
	EXPECT_EQ(data2["3"],"3");

	Json::Value data3 = db.getHigherKeyValue(4);
	EXPECT_EQ(data3["1"],"1");

	Json::Value data4 = db.getHigherKeyValue(535);
	EXPECT_TRUE(data4.isMember("error"));

	EXPECT_TRUE(db.Delete("A"));

	SettingManager::deleteInstance();

}
