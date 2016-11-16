#include <modeltest/JobTest.h>
#include <model/Job.h>
#include <model/JobPosition.h>
#include <exception/JobException.h>
#include <extern/json.h>

using namespace std;

TEST(JobTest, createJob) {
	string name = "cebador";
	string category = "software";
	string description = "El señor que ceba mates.";

	Json::Value data;
	data["name"] = name;
	data["category"] = category;
	data["description"] = description;

	JobPosition jobPosition = JobPosition::create(data);
	Job* job;

	EXPECT_NO_THROW(job = new Job("2010-10-25 16:22:00","2011-10-25 16:22:00","Totos",jobPosition.getName()));

	Json::Value asJson = job->asJSON();

	EXPECT_EQ(asJson["date_since"].asString(),"2010-10-25 16:22:00");
	EXPECT_EQ(asJson["date_to"].asString(),"2011-10-25 16:22:00");
	EXPECT_EQ(asJson["company"].asString(),"Totos");
	EXPECT_EQ(asJson["position"],jobPosition.asJSON());

	jobPosition.delet();
	delete job;
}
