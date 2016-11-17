#include <modeltest/JobTest.h>
#include <model/Job.h>
#include <model/JobPosition.h>
#include <exception/JobException.h>
#include <extern/json.h>
#include <list>

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

	Json::Value data2;
	data2["date_since"] = "2010-10-25 16:22:00";
	data2["date_to"] = "2011-10-25 16:22:00";
	data2["company"] = "Totos";
	data2["position"] = data;

	EXPECT_TRUE(Job::check(data2).empty());

	EXPECT_NO_THROW(job = new Job(data2["date_since"].asString(),data2["date_to"].asString(),data2["company"].asString(),jobPosition.getName()));

	Json::Value asJson = job->asJSON();

	EXPECT_EQ(asJson["date_since"].asString(),data2["date_since"].asString());
	EXPECT_EQ(asJson["date_to"].asString(),data2["date_to"].asString());
	EXPECT_EQ(asJson["company"].asString(),data2["company"].asString());
	EXPECT_EQ(asJson["position"],jobPosition.asJSON());

	jobPosition.delet();
	delete job;
}

TEST(JobTest, JobToJSONList) {
	string name = "cebador";
	string category = "software";
	string description = "El señor que ceba mates.";

	Json::Value data;
	data["name"] = name;
	data["category"] = category;
	data["description"] = description;

	JobPosition jobPosition = JobPosition::create(data);

	list<Job> jobs;

	Job job = Job("2010-10-25 16:22:00","2011-10-25 16:22:00","Totos",jobPosition.getName());
	Job job2 = Job("2015-10-25 16:22:00","","FIUBA",jobPosition.getName());
	Job job3 = Job("1995-10-25 16:22:00","2000-10-25 16:22:00","UTN",jobPosition.getName());

	jobs.push_back(job);
	jobs.push_back(job2);
	jobs.push_back(job3);

	Json::Value json = Job::listToArray(jobs);

	EXPECT_FALSE(json.empty());

	jobPosition.delet();
}



TEST(JobTest, JobErrorTest) {
	Json::Value invalidPosition;
	invalidPosition["name"] = "invalid";
	invalidPosition["position"] = "invalid position";

	EXPECT_THROW(Job("asd","asd","asd",invalidPosition),JobException);

	Json::Value invalidJob;
	invalidJob["position"] = invalidPosition;

	ErrorMessage error = Job::check(invalidJob);
	EXPECT_FALSE(error.empty());

}
