#ifndef SRC_MAIN_SRC_SERVICE_OBJECTS_USER_H_
#define SRC_MAIN_SRC_SERVICE_OBJECTS_USER_H_

namespace std {

class User {
private:
	string full_name,first_name,last_name,id,description,date_of_birth,email,profile_picture;
	Job* current_job;
	list<Job*> past_jobs;
	//list<Skill*> skills;
	//list<Education*> education;
	//list<Recomendation*> recomendations_received;

public:
	User(string user_id);

	bool create(map<string,string> data);

	virtual ~User();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_SERVICE_OBJECTS_USER_H_ */
