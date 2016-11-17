#include <modeltest/UserTest.h>
#include <model/User.h>
#include <model/JobPosition.h>
#include <model/Skill.h>
#include <exception/UserException.h>
#include <extern/json.h>
#include <settings/SettingManager.h>

#include <iostream>
#include <fstream>

void settinUpDBFolderForModel() {
	string json = "{\"db_folder\" : \".temp-test/\"}\n";

	ofstream out(".temp-test/setting-model.json");
	out << json;
	out.close();

	SettingManager::getInstance()->readFile(".temp-test/setting-model.json");
}

TEST(UserTest, existUser){
	settinUpDBFolderForModel();
	EXPECT_FALSE(User::exist("invalid user"));
}


TEST(UserTest, createBasicUser){
	settinUpDBFolderForModel();
	string id = "fme";

	Json::Value data;
	data["id"] = id;
	data["first_name"] = "Facundo";
	data["last_name"] = "Etchanchu";
	data["description"] = "Yo papá, quién si no.";
	data["email"] = "fme@lincedin.com";
	data["date_of_birth"] = "1964-04-12 16:22:00";
	data["profile_picture"] = "ASD123456";
	data["password"] = "123456";

	EXPECT_FALSE(User::exist(id));

	EXPECT_THROW(User user = User(id),UserException);

	User user = User::create(data);

	Json::Value jsonUser = user.asJSON();

	EXPECT_EQ(jsonUser["id"],data["id"]);
	EXPECT_EQ(jsonUser["first_name"],data["first_name"]);
	EXPECT_EQ(jsonUser["last_name"],data["last_name"]);
	EXPECT_EQ(jsonUser["description"],data["description"]);
	EXPECT_EQ(jsonUser["email"],data["email"]);
	EXPECT_EQ(jsonUser["date_of_birth"],data["date_of_birth"]);

	EXPECT_TRUE(User::exist(id));

	User::delet(id);

	EXPECT_FALSE(User::exist(id));
}

TEST(UserTest, createCompleteUser){
	settinUpDBFolderForModel();
	settinUpDBFolderForModel();

	string id = "fme";

	Json::Value data;
	data["id"] = id;
	data["first_name"] = "Facundo";
	data["last_name"] = "Etchanchu";
	data["description"] = "Yo papá, quién si no.";
	data["email"] = "fme@lincedin.com";
	data["date_of_birth"] = "1964-04-12 16:22:00";
	data["profile_picture"] = "ASD123456";
	data["password"] = "123456";
	data["education"] = Json::arrayValue;
	data["jobs"] = Json::arrayValue;
	data["skills"] = Json::arrayValue;

	Json::Value ed1;
	ed1["start_date"] = "1981-03-12 16:22:00";
	ed1["end_date"] = "1990-12-12 23:22:00";
	ed1["school_name"] = "FIUBA";
	ed1["degree"] = "Ingeniero en casi todo";
	data["education"].append(ed1);
	data["education"].append(ed1);

	JobPosition job_p = JobPosition("developer");

	Json::Value job;
	job["date_since"] = "2012-10-25 16:22:00";
	job["date_to"] = "2016-10-25 16:22:00";
	job["company"] = "FIUBA";
	job["position"] = job_p.asJSON();

	data["jobs"].append(job);

	Skill skill = Skill("Java");
	Skill skill2 = Skill("c");
	data["skills"].append(skill.asJSON());
	data["skills"].append(skill2.asJSON());

	EXPECT_FALSE(User::exist(id));

	User user = User::create(data);

	Json::Value jsonUser = user.asJSON();

	EXPECT_EQ(jsonUser["id"],data["id"]);
	EXPECT_EQ(jsonUser["first_name"],data["first_name"]);
	EXPECT_EQ(jsonUser["last_name"],data["last_name"]);
	EXPECT_EQ(jsonUser["description"],data["description"]);
	EXPECT_EQ(jsonUser["email"],data["email"]);
	EXPECT_EQ(jsonUser["date_of_birth"],data["date_of_birth"]);
	EXPECT_EQ(jsonUser["education"],data["education"]);
	EXPECT_EQ(jsonUser["jobs"],data["jobs"]);
	EXPECT_EQ(jsonUser["skills"],data["skills"]);

	EXPECT_TRUE(User::exist(id));

	User::delet(id);

	EXPECT_FALSE(User::exist(id));
}

