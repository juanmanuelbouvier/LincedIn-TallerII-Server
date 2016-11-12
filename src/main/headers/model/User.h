#ifndef SRC_MAIN_SRC_MODEL_USER_H_
#define SRC_MAIN_SRC_MODEL_USER_H_

#include <list>
#include <model/Job.h>
#include <model/Skill.h>
#include <model/Education.h>
#include <model/Recommendation.h>

namespace std {

class User{
private:
	string id,full_name,first_name,last_name,description,date_of_birth,email,profile_picture;
	list<Job> jobs;

	list<Skill> skills;
	list<Education> education;
	list<Recommendation> recommendations_received;

public:
	User(string user_id);

	static User create( Json::Value data );
	Json::Value asJSON();
	static bool exist(string user_id);
	static map<string,string> check(Json::Value data);

	virtual ~User();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_MODEL_USER_H_ */
