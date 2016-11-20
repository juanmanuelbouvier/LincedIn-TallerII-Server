#include <modeltest/GeolocalizationTests.h>

#include <settings/SettingManager.h>
#include <utils/DateUtils.h>
#include <TestHelper.h>

#include <model/User.h>
#include <model/Geolocalization.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


void GeolocalizationTests::settinUpDBFolderForModel() {
	string json = "{\"db_folder\" : \".temp-test/\"}\n";

	ofstream out(".temp-test/setting-model.json");
	out << json;
	out.close();

	SettingManager::getInstance()->readFile(".temp-test/setting-model.json");
}


TEST(GeolocalizationTests, findUserEmpty) {
	TestHelper::settinUpTestModel();
	Json::Value location;
	location["latitude"] = -25.298;
	location["longitude"] = -57.596;
	Json::Value result = Geolocalization::findUsersByLocation(location);

	EXPECT_TRUE( result.isNull() );
}


TEST(GeolocalizationTests, updateUserLocation) {
	TestHelper::settinUpTestModel();

	EXPECT_TRUE( Geolocalization::remove("a user id") );

	string user1 = "u1";
	Json::Value result = Geolocalization::getUserLocation(user1);
	EXPECT_TRUE( result.isNull() );

	User u1 = TestHelper::createBasicUsers(user1);
	Json::Value data;
	data["user_id"] = user1;
	data["latitude"] = -25.2967829;
	data["longitude"] = -57.5946782;

	EXPECT_TRUE( Geolocalization::updateLocation(data) );

	int timestamp = DateUtils::timestamp();
	Json::Value result2 = Geolocalization::getUserLocation(user1);
	Json::Value expected2;
	expected2["timestamp"] = timestamp;
	Json::Value geo;
	geo["latitude"] = -25.2967829;
	geo["longitude"] = -57.5946782;
	expected2["geolocalization"] = geo;

	EXPECT_EQ(result2["timestamp"].asString(),expected2["timestamp"].asString());
	EXPECT_EQ(result2["geolocalization"]["latitude"].asString(),expected2["geolocalization"]["latitude"].asString());
	EXPECT_EQ(result2["geolocalization"]["longitude"].asString(),expected2["geolocalization"]["longitude"].asString());
	EXPECT_EQ(result2,expected2);

	Json::Value data3;
	data3["latitude"] = -94.590781;
	EXPECT_FALSE( Geolocalization::updateLocation(data3) );
	data3["longitude"] = -58.416437;
	EXPECT_FALSE( Geolocalization::updateLocation(data3) );
	data3["user_id"] = user1;
	EXPECT_FALSE( Geolocalization::updateLocation(data3) );
	data3["latitude"] = -34.590781;

	int timestamp3 = DateUtils::timestamp();
	EXPECT_TRUE( Geolocalization::updateLocation(data3) );

	Json::Value expected3;
	expected3["timestamp"] = timestamp3;
	Json::Value geo3;
	geo3["latitude"] = -34.590781;
	geo3["longitude"] = -58.416437;
	expected3["geolocalization"] = geo3;

	Json::Value result3 = Geolocalization::getUserLocation(user1);
	EXPECT_EQ(result3["timestamp"].asString(),expected3["timestamp"].asString());
	EXPECT_EQ(result3["geolocalization"]["latitude"].asString(),expected3["geolocalization"]["latitude"].asString());
	EXPECT_EQ(result3["geolocalization"]["longitude"].asString(),expected3["geolocalization"]["longitude"].asString());
	EXPECT_EQ(result3,expected3);

	EXPECT_TRUE( Geolocalization::remove(user1) );
	Json::Value result4 = Geolocalization::getUserLocation(user1);
	EXPECT_TRUE( result4.isNull() );

}


TEST(GeolocalizationTests, findPeopleInRange) {
	TestHelper::settinUpTestModel();

	User u1 = TestHelper::createBasicUsers("theUser1");
	Json::Value data1;
	data1["user_id"] = u1.getID();
	data1["latitude"] = -25.2967829;
	data1["longitude"] = -57.5946782;
	EXPECT_TRUE( Geolocalization::updateLocation(data1) );

	//0.41 km to u1
	User u2 = TestHelper::createBasicUsers("theUser2");
	Json::Value data2;
	data2["user_id"] = u2.getID();
	data2["latitude"] = -25.296966;
	data2["longitude"] = -57.598711;
	EXPECT_TRUE( Geolocalization::updateLocation(data2) );

	//1.45 km to u1
	User u3 = TestHelper::createBasicUsers("theUser3");
	Json::Value data3;
	data3["user_id"] = u3.getID();
	data3["latitude"] = -25.302980;
	data3["longitude"] = -57.589916;
	EXPECT_TRUE( Geolocalization::updateLocation(data3) );

	//9.09 km to u1
	User u4 = TestHelper::createBasicUsers("theUser4");
	Json::Value data4;
	data4["user_id"] = u4.getID();
	data4["latitude"] = -25.215364;
	data4["longitude"] = -57.583273;
	EXPECT_TRUE( Geolocalization::updateLocation(data4) );

	//100m to u1
	Json::Value dataSearch;
	dataSearch["latitude"] = -25.295881;
	dataSearch["longitude"] = -57.594842;
	dataSearch["range"] = 0.09;
	Json::Value r1 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_TRUE(r1.isNull());

	dataSearch["range"] = 0.11;
	Json::Value r2 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_EQ(r2.size(),1);
	EXPECT_FALSE(r2[u1.getID()].isNull());

	dataSearch["range"] = 0.43;
	Json::Value r3 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_EQ(r3.size(),2);
	EXPECT_FALSE(r3[u1.getID()].isNull());
	EXPECT_FALSE(r3[u2.getID()].isNull());

	dataSearch["range"] = 1.48;
	Json::Value r4 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_EQ(r4.size(),3);
	EXPECT_FALSE(r4[u1.getID()].isNull());
	EXPECT_FALSE(r4[u2.getID()].isNull());
	EXPECT_FALSE(r4[u3.getID()].isNull());

	dataSearch["range"] = 9;
	Json::Value r5 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_EQ(r5.size(),3);
	EXPECT_FALSE(r5[u1.getID()].isNull());
	EXPECT_FALSE(r5[u2.getID()].isNull());
	EXPECT_FALSE(r5[u3.getID()].isNull());

	dataSearch["range"] = 12;
	Json::Value r6 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_EQ(r6.size(),4);
	EXPECT_FALSE(r6[u1.getID()].isNull());
	EXPECT_FALSE(r6[u2.getID()].isNull());
	EXPECT_FALSE(r6[u3.getID()].isNull());
	EXPECT_FALSE(r6[u4.getID()].isNull());

	dataSearch["range"] = 100;
	Json::Value r7 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_EQ(r7.size(),4);

	dataSearch["range"] = 301;
	Json::Value r8 = Geolocalization::findUsersByLocation(dataSearch);
	EXPECT_FALSE(r8["error"].isNull());

}
