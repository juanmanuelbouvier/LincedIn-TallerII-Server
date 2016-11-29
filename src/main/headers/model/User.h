#ifndef SRC_MAIN_SRC_MODEL_USER_H_
#define SRC_MAIN_SRC_MODEL_USER_H_

#include <list>
#include <model/Job.h>
#include <model/Skill.h>
#include <model/Education.h>
#include <model/Recommendation.h>
#include <services/DB/DBManager.h>
#include <utils/ErrorMessage.h>

using namespace std;

class User{
private:
	string id,full_name,first_name,last_name,description,date_of_birth,email,profile_picture,firebase_id;
	list<Job> jobs;
	list<Skill> skills;
	list<Education> education;
	int register_timestamp,last_edit_timestamp;
	static DB* getDB();
	static DB* getEmailDB();
	static string generateUserID(string candidate,string first_name, string last_name);

public:
	User(string user_id);

	static User create( Json::Value data );
	static Json::Value getAllUsers();
	static bool remove( string user_id);
	static ErrorMessage update(string user_id, Json::Value data);
	static bool exist(string user_id);
	static ErrorMessage check(Json::Value data);
	static string getIdByEmail(string email );
	static bool checkPassword( string user_id,string password );
	Json::Value asJSON();
	string getID();
	string getFirebaseID();

	virtual ~User();
};

#endif /* SRC_MAIN_SRC_MODEL_USER_H_ */
