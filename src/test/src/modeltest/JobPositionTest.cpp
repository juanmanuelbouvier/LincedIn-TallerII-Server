#include <modeltest/JobPositionTest.h>
#include <model/JobPosition.h>
#include <exception/JobException.h>

using namespace std;

TEST(JobPositionTest, ExistJobPosition){
	EXPECT_TRUE(JobPosition::exist("developer"));
	EXPECT_FALSE(JobPosition::exist("algo que jamas exista"));
}

TEST(JobPositionTest, JobPositionGeneralTest){
	string name = "Cebador";
	string category = "software";
	string description = "El señor que ceba mates.";

	Json::Value data;
	data["name"] = name;
	data["category"] = category;
	data["description"] = description;


	JobPosition job = JobPosition::create(data);

	EXPECT_EQ(job.asJSON(),data);

	EXPECT_EQ(job.getName(), name);
	EXPECT_EQ(job.getCategory(), category);
	EXPECT_EQ(job.getDescription(), description);

	EXPECT_TRUE(job.setDescription("asd"));
	EXPECT_EQ(job.getDescription(), "asd");

	EXPECT_TRUE(job.setName("cebador"));
	EXPECT_EQ(job.getName(), "cebador");

	EXPECT_TRUE(job.setCategory("music"));
	EXPECT_EQ(job.getCategory(), "music");

	EXPECT_TRUE(job.delet());
}

TEST(JobPositionTest, createJobPositionInvalidCategory){
	Json::Value data;
	data["name"] = "name";
	data["category"] = "Invalid category";
	data["description"] = "job with invalid category";

	EXPECT_THROW(JobPosition::create(data),JobException);
}

TEST(JobPositionTest, JobPositionInvalidName){
	EXPECT_THROW(JobPosition("invalid name"),JobException);
}
