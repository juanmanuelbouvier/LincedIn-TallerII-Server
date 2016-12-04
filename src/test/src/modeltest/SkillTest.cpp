#include <modeltest/SkillTest.h>
#include <model/Skill.h>
#include <exception/SkillException.h>
#include <TestHelper.h>

#include <iostream>

using namespace std;

TEST(SkillTest, ExistSkill){
	TestHelper::settinUpTestModel();

	string name = "Java";
	string name_invalid = "algo que jamas exista";

	EXPECT_TRUE(Skill::exist(name));
	EXPECT_FALSE(Skill::exist(name_invalid));

	EXPECT_THROW(Skill skill(name_invalid),SkillException);

	Json::Value invalid;
	EXPECT_FALSE(Skill::exist(invalid));

	invalid["name"] = "invalid name";
	invalid["description"] = "invalid";
	invalid["category"] = 123;

	EXPECT_FALSE(Skill::exist(invalid));
	EXPECT_THROW(Skill::create(invalid),SkillException);

	Json::Value emptyjson;

	EXPECT_THROW(Skill::create(emptyjson),SkillException);

	invalid["name"] = "Java";
	EXPECT_FALSE(Skill::exist(invalid));

}


TEST(SkillTest, createSkill){
	TestHelper::settinUpTestModel();

	string name = "Go";
	string category = "software";
	string description = "Lenguaje de programación Go";

	EXPECT_FALSE(Skill::exist(name));

	Json::Value valid;
	valid["name"] = name;
	valid["category"] = category;
	valid["description"] = description;

	EXPECT_NO_THROW(Skill::create(valid));

	EXPECT_TRUE(Skill::exist(valid));

	Skill skill = Skill(name);

	EXPECT_EQ(skill.getName(),name);
	EXPECT_EQ(skill.getDescription(),description);
	EXPECT_EQ(skill.getCategory(),category);

	EXPECT_TRUE(skill.remove());
}


TEST(SkillTest, updateSkill){
	TestHelper::settinUpTestModel();

	string name = "Go";
	string category = "software";
	string description = "Lenguaje de programación Go";

	EXPECT_FALSE(Skill::exist(name));

	Json::Value valid;
	valid["name"] = name;
	valid["category"] = category;
	valid["description"] = description;

	Skill skill = Skill::create(valid);

	string new_name = "Go";
	string new_category = "music";
	string new_description = "Música Go";


	EXPECT_TRUE(skill.setName(new_name));
	EXPECT_EQ(skill.getName(),new_name);

	EXPECT_TRUE(skill.setDescription(new_description));
	EXPECT_EQ(skill.getDescription(),new_description);

	EXPECT_TRUE(skill.setCategory(new_category));
	EXPECT_EQ(skill.getCategory(),new_category);

	EXPECT_TRUE(skill.remove());
}
