#include <modeltest/UserTest.h>
#include <model/User.h>
#include <exception/UserException.h>
#include <extern/json.h>

#include <iostream>

TEST(UserTest, existUser){
	EXPECT_FALSE(User::exist("invalid user"));
}


TEST(UserTest, createBasicUser){

	string id = "fme";

	Json::Value data;
	data["id"] = id;
	data["first_name"] = "Facundo";
	data["last_name"] = "Etchanchu";
	data["description"] = "Yo papá, quién si no.";
	data["email"] = "fme@lincedin.com";
	data["date_of_birth"] = "1964-04-12 16:22:00";
	data["profile_picture"] = "ASD123456";

	EXPECT_FALSE(User::exist(id));

	EXPECT_THROW(User user = User(id),UserException);

	User user = User::create(data);

	Json::Value jsonUser = user.asJSON();

	cout << jsonUser.toStyledString() << endl;

	EXPECT_EQ(jsonUser["id"],data["id"]);
	EXPECT_EQ(jsonUser["first_name"],data["first_name"]);
	EXPECT_EQ(jsonUser["last_name"],data["last_name"]);
	EXPECT_EQ(jsonUser["description"],data["description"]);
	EXPECT_EQ(jsonUser["email"],data["email"]);
	EXPECT_EQ(jsonUser["date_of_birth"],data["date_of_birth"]);
	EXPECT_EQ(jsonUser["profile_picture"],data["profile_picture"]);

	EXPECT_TRUE(User::exist(id));

	User::delet(id);

	EXPECT_FALSE(User::exist(id));
}

TEST(UserTest, createCompleteUser){

	string id = "fme";

	Json::Value data;
	data["id"] = id;
	data["first_name"] = "Facundo";
	data["last_name"] = "Etchanchu";
	data["description"] = "Yo papá, quién si no.";
	data["email"] = "fme@lincedin.com";
	data["date_of_birth"] = "1964-04-12 16:22:00";
	data["profile_picture"] = "ASD123456";
	data["education"] = Json::arrayValue;


	EXPECT_FALSE(User::exist(id));

	User user = User::create(data);

	Json::Value jsonUser = user.asJSON();

	EXPECT_EQ(jsonUser["id"],data["id"]);
	EXPECT_EQ(jsonUser["first_name"],data["first_name"]);
	EXPECT_EQ(jsonUser["last_name"],data["last_name"]);
	EXPECT_EQ(jsonUser["description"],data["description"]);
	EXPECT_EQ(jsonUser["email"],data["email"]);
	EXPECT_EQ(jsonUser["date_of_birth"],data["date_of_birth"]);
	EXPECT_EQ(jsonUser["profile_picture"],data["profile_picture"]);

	EXPECT_TRUE(User::exist(id));

	User::delet(id);

	EXPECT_FALSE(User::exist(id));
}

