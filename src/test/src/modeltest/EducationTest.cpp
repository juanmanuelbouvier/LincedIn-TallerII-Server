#include <modeltest/EducationTest.h>
#include <model/Education.h>
#include <extern/json.h>
#include <string>
#include <list>

using namespace std;

TEST(EducationTest, EducationAsJSON){
	string start = "1981-03-12 16:22:00";
	string end = "1990-12-12 23:22:00";
	string school = "FIUBA";
	string degree = "Ingeniero en Informática";

	Education education = Education(start,end,school,degree);

	Json::Value jsonEducation = education.asJSON();

	EXPECT_EQ(start,jsonEducation["start_date"].asString());
	EXPECT_EQ(end,jsonEducation["end_date"].asString());
	EXPECT_EQ(school,jsonEducation["school_name"].asString());
	EXPECT_EQ(degree,jsonEducation["degree"].asString());

}

TEST(EducationTest, EducationListAsJSON){
	string start = "1981-03-12 16:22:00";
	string end = "1990-12-12 23:22:00";
	string school = "FIUBA";
	string degree = "Ingeniero en Informática";
	string degree2 = "Ingeniero Industrial";

	list<Education> education;

	Education* ed1 = new Education(start,end,school,degree);
	Education ed2 = Education(end,"",school,degree2);

	education.push_back(*ed1);
	education.push_back(ed2);

	Json::Value listOriginal = Json::Value(Json::arrayValue);
	listOriginal.append(ed1->asJSON());
	listOriginal.append(ed2.asJSON());

	Json::Value list = Education::listToArray(education);

	EXPECT_EQ(list,listOriginal);

	delete ed1;
}

TEST(EducationTest, EducationErrorTest){
	Json::Value invalid;
	EXPECT_FALSE(Education::check(invalid));
}
