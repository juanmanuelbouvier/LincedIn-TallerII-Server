#include <modeltest/UserTest.h>
#include <model/User.h>
#include <model/JobPosition.h>
#include <model/Job.h>
#include <model/Skill.h>
#include <exception/UserException.h>
#include <extern/json.h>
#include <TestHelper.h>

TEST(UserTest, existUser){
	TestHelper::settinUpTestModel();
	EXPECT_FALSE(User::exist("invalid user"));
}


TEST(UserTest, createBasicUser){
	TestHelper::settinUpTestModel();
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
	EXPECT_EQ(user.getID(),id);
	EXPECT_EQ(jsonUser["first_name"],data["first_name"]);
	EXPECT_EQ(jsonUser["last_name"],data["last_name"]);
	EXPECT_EQ(jsonUser["description"],data["description"]);
	EXPECT_EQ(jsonUser["email"],data["email"]);
	EXPECT_EQ(jsonUser["date_of_birth"],data["date_of_birth"]);

	EXPECT_TRUE(User::exist(id));

	User::remove(id);

	EXPECT_FALSE(User::exist(id));
}

TEST(UserTest, createCompleteUser){
	TestHelper::settinUpTestModel();

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

	JobPosition job_p = JobPosition("project manager");

	Json::Value job;
	job["date_since"] = "2012-10-25 16:22:00";
	job["date_to"] = "2016-10-25 16:22:00";
	job["company"] = "FIUBA";
	job["position"] = job_p.asJSON();

	data["jobs"].append(job);



	Skill skill = TestHelper::createSkill("Java","software","Lenguaje de programación Java");
	Skill skill2 = TestHelper::createSkill("c","software","Lenguaje de programación C");;
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
	EXPECT_EQ(id,User::getIdByEmail(data["email"].asString()));
	EXPECT_EQ(jsonUser["date_of_birth"],data["date_of_birth"]);
	EXPECT_EQ(jsonUser["education"],data["education"]);
	EXPECT_EQ(jsonUser["jobs"],data["jobs"]);
	EXPECT_EQ(jsonUser["skills"],data["skills"]);

	EXPECT_TRUE(User::exist(id));
	EXPECT_TRUE(User::checkPassword(id,data["password"].asString()));

	User::remove(id);

	EXPECT_FALSE(User::exist(id));
}

TEST(UserTest, updateUser){
	TestHelper::settinUpTestModel();

	string id = "fme";

	User user = TestHelper::createUser(id);

	Json::Value dataUpdate = user.asJSON();


	//skills
	string name_skill = "Perl";
	if (Skill::exist(name_skill)){
		Skill skill = Skill(name_skill);
		dataUpdate["skills"].append(skill.asJSON());
	}

	//jobs
	string position_name = "dj";
	Job job = Job("2016-10-10 12:00:00","","ACO",position_name);
	dataUpdate["jobs"].append(job.asJSON());


	//update email
	dataUpdate["email"] = "fme@gmail.com";

	ErrorMessage error = User::update(id,dataUpdate);

	EXPECT_FALSE(error);

	user = User(id);

	Json::Value finalUser = user.asJSON();

	EXPECT_EQ(finalUser["id"],dataUpdate["id"]);
	EXPECT_EQ(finalUser["first_name"],dataUpdate["first_name"]);
	EXPECT_EQ(finalUser["last_name"],dataUpdate["last_name"]);
	EXPECT_EQ(finalUser["description"],dataUpdate["description"]);
	EXPECT_EQ(finalUser["email"],dataUpdate["email"]);
	EXPECT_EQ(finalUser["date_of_birth"],dataUpdate["date_of_birth"]);
	EXPECT_EQ(finalUser["education"],dataUpdate["education"]);
	EXPECT_EQ(finalUser["jobs"],dataUpdate["jobs"]);
	EXPECT_EQ(finalUser["skills"],dataUpdate["skills"]);

	User::remove(id);
}

TEST(UserTest, ErrorUser){
	TestHelper::settinUpTestModel();

	Json::Value emptyData;

	EXPECT_THROW(User::create(emptyData),UserException);

	EXPECT_FALSE(User::remove("Invalid user"));

	EXPECT_TRUE(User::update("Invalid user",emptyData));
}

TEST(UserTest, AddTwoUserWithEqualID){
	TestHelper::settinUpTestModel();

	string id = "fme";

	User user = TestHelper::createUser(id);

	Json::Value data = user.asJSON();
	data["password"] = "ASD123";

	User user2 = User::create(data);

	EXPECT_NE(id,user2.getID());
}



