#include <model/User.h>
#include <utils/JSONUtils.h>
#include <utils/DateUtils.h>
#include <utils/StringUtils.h>
#include <iostream>
#include <services/Logger/Logger.h>
#include <services/Access/AccessToken.h>
#include <exception/SkillException.h>
#include <exception/UserException.h>
#include <exception/JobException.h>

#define USER_DB "User"
#define TOKEN_VALID_SECONDS 10*24*60 // 10 days

namespace std {

User User::create( Json::Value data ) {

	ErrorMessage error = check(data);

	if (!error.empty()){
		cout << Log("User.cpp::" + to_string(__LINE__) + ". Error on create skill, check data ",ERROR) << endl;
		throw new UserException("Error on create user, check data. Summary: " + error.summary());
	}

	string user_id = data["id"].asString();
	Json::Value userDB;
	userDB["first_name"] = data["first_name"];
	userDB["last_name"] = data["last_name"];
	userDB["description"] = data["description"];
	userDB["email"] = data["email"];
	userDB["date_of_birth"] = data["date_of_birth"];
	userDB["profile_picture"] = data["profile_picture"];
	userDB["skills_names"] = data["skills_names"];
	userDB["jobs"] = data["jobs"];
	userDB["education"] = data["education"];
	userDB["recommendations_received"] = data["recommendations_received"];

	userDB["password"] = StringUtils::passwordEncrypt(data["password"].toStyledString());
	int now = DateUtils::timestamp();
	userDB["register_timestamp"] = now;
	userDB["last_edit_timestamp"] =  now;

	if (getDB()->storeJSON(user_id, userDB)){
		return User(user_id);
	}

	Log("Chat.cpp::" + to_string(__LINE__) + ". Cannot store user in DB",ERROR);
	throw new UserException("Error on store user in DB");
}

bool User::delet( string user_id){
	//getDB()->delete(user_id);

	return false;
}

ErrorMessage User::update(string user_id,Json::Value data){
	ErrorMessage error;
	Json::Value userDB = getDB()->getJSON(user_id);

	if (userDB.isMember("error")){
		error.addError("user_id","Not find user id in DB");
		return error;
	}

	ErrorMessage checkMessage = User::check(data);
	if (!checkMessage.empty()) return checkMessage;

	//no public information
	data["register_timestamp"] = userDB["register_timestamp"].asInt();
	data["last_edit_timestamp"] = DateUtils::timestamp();
	data["password"] = userDB["password"];

	if (!getDB()->storeJSON(user_id,data)){
		error.addError(user_id,"Error on store data in DB");
	}

	return error;
}

User::User(string user_id) {

	//MOCK
	id = user_id;
	first_name = "Carlos";
	last_name = "Fontela";
	full_name = first_name + " " + last_name;
	description = "El capo de la FIUBA";
	email =  user_id + "@lincedin.com";
	date_of_birth = "1964-04-12 16:22:00";
	profile_picture = "https://cysingsoft.files.wordpress.com/2009/01/carlosfontela6.jpg?w=450";

	int now = DateUtils::timestamp();
	register_timestamp = now;
	last_edit_timestamp =  now;

	try{
		Skill java = Skill("Java");
		skills.push_back(java);
		Skill c = Skill("c");
		skills.push_back(c);
	} catch (SkillException& e){
		cout << Log("User.cpp::" + to_string(__LINE__) + ". create skill " + e.what() ,ERROR) << endl;
		throw new UserException("Error on create skill");
	}

	try {
		Job job1 = Job("2010-10-25 16:22:00","2011-10-25 16:22:00","Totos","project manager");
		jobs.push_back(job1);

		Job job2 = Job("2012-10-25 16:22:00","2016-10-25 16:22:00","FIUBA","developer");
		jobs.push_back(job2);

		Job current = Job("2016-10-25 17:22:00","","Esperanto","dj");
		jobs.push_back(current);
	} catch (JobException& je){
		cout << Log("User.cpp::" + to_string(__LINE__) + ". Error on create job" + je.what() ,ERROR) << endl;
		throw new UserException("Error on create Job");
	}


	Education ed = Education("1981-03-12 16:22:00","1990-12-12 23:22:00","FIUBA","Ingeniero en casi todo");
	education.push_back(ed);


	Recommendation red = Recommendation("Nico Paez", "Éste es un crack, se auto cita en las diapos.",now);
	recommendations_received.push_back(red);


	//real
	/*
	Json::Value userDB = getDB()->getJSON(user_id);
	if (userDB.isMember("error")){
		cout << Log("User.cpp::" + to_string(__LINE__) + ". Error on create user " + userDB["error"].toStyledString() ,ERROR) << endl;
		throw new UserException("User invalid.");
	}

	id = user_id;
	first_name = userDB["first_name"];
	last_name = userDB["last_name"];
	full_name = first_name + " " + last_name;
	description = userDB["description"];
	email =  userDB["email"];
	date_of_birth = userDB["date_of_birth"];
	profile_picture = userDB["profile_picture"];

	if (userDB.isMember("skills_names")){
		Json::Value skills_name = userDB["skills_names"];
		for( Json::ValueIterator itr = skills_name.begin() ; itr != skills_name.end() ; itr++ ) {
			string skill_name = skills_name[itr.index()].toStyledString();
			try{
				Skill skill = Skill(skill_name);
				skills.push_back(skill);
			} catch (SkillException& e){
				cout << Log("User.cpp::" + to_string(__LINE__) + ". create skill " + skill_name + ". " + e.what() ,ERROR) << endl;
					throw new UserException("Error on create skill " + skill_name);
			}
		}
	}

	if (userDB.isMember("jobs")){
		Json::Value jobs_data = userDB["jobs"];
		for( Json::ValueIterator itr = jobs_data.begin() ; itr != jobs_data.end() ; itr++ ) {
			Json::Value job_data = jobs_data[itr.index()];
			try{
				Job job = Job(job_data["date_since"].toStyledString(),job_data.get("date_to","").toStyledString(),job_data["company"].toStyledString(),job_data["name_position"].toStyledString());
				jobs.push_back(job);
			} catch (JobException& e){
				cout << Log("User.cpp::" + to_string(__LINE__) + ". create job. " + e.what() ,ERROR) << endl;
					throw new UserException("Error on create Job");
			}
		}
	}

	if (userDB.isMember("education")){
		Json::Value education_data = userDB["education"];
		for( Json::ValueIterator itr = education_data.begin() ; itr != education_data.end() ; itr++ ) {
			Json::Value ed_data = education_data[itr.index()];
			Education ed = Education(ed_data["start_date"].toStyledString(),ed_data.get("end_date","").toStyledString(), ed_data["school_name"].toStyledString(),ed_data["degree"].toStyledString());
			education.push_back(ed);
		}
	}

	if (userDB.isMember("recommendations_received")){
		Json::Value recommendation = userDB["recommendations_received"];
		for( Json::ValueIterator itr = recommendation.begin() ; itr != recommendation.end() ; itr++ ) {
			Json::Value red_data = recommendation[itr.index()];
			Recommendation rec = Recommendation(red_data["recommender"].toStyledString(),red_data["text"].toStyledString(),red_data["timestamp"].asInt());
			recommendations_received.push_back(rec);
		}
	}
	*/
}


DB* User::getDB(){
	return DBManager::getDB(USER_DB);
}

ErrorMessage User::check(Json::Value data){
	ErrorMessage error;

	if (data.isMember("id")){
		//Json::Value userInDB = getDB()->getJSON(data["id"].toStyledString());
	}else {
		error.addError("id","Id not specified");
	}

	if (!data.isMember("first_name")){
		error.addError("first_name","first name not specified");
	}

	if (!data.isMember("last_name")){
		error.addError("last_name","Last name not specified");
	}

	if (!data.isMember("email")){
		error.addError("email","Email not specified");
	}

	if (data.isMember("skills_names")){
		Json::Value skills = data["skills_name"];
		for( Json::ValueIterator itr = skills.begin() ; itr != skills.end() ; itr++ ) {
			Json::Value val = skills[itr.index()];
			if (! Skill::exist(val.toStyledString()) ) {
				error.addError("skill_"+ val.toStyledString(),"Skill invalid (" + val.toStyledString() + ").");
			}
		}
	}

	if (data.isMember("jobs")){
			Json::Value jobs = data["jobs"];
			for( Json::ValueIterator itr = jobs.begin() ; itr != jobs.end() ; itr++ ) {
				Json::Value val = jobs[itr.index()];
				ErrorMessage error_job = Job::check(val);
				if (!error_job.empty()) {
					error.addError("Job_"+val.toStyledString(),"Job invalid (" + val.toStyledString() + ").");
				}
			}
		}

	return error;
}

bool User::exist(string user_id){

	string  res = getDB()->get(user_id);
	if (res.compare("")){
		return false;
	}
	return true;
}


string User::getIdByEmail(string email ){
	return "";
	//TODO
}

string User::generateSessionToken( string user_id ){
	Json::Value token;
	token["user_id"] = user_id;
	token["timestamp"] = DateUtils::timestamp();

	return AccessToken::encode(token);
}

bool User::validToken(string token){
	Json::Value decodeToken = AccessToken::decode(token);
	int now = DateUtils::timestamp();
	int token_timestamp = decodeToken["timestamp"].asInt();

	if (now - token_timestamp <= TOKEN_VALID_SECONDS ){
		return true;
	}
	return false;
}

string User::userIdByToken( string token ){

	if (!validToken(token)){
		return "";
	}

	Json::Value decodeToken = AccessToken::decode(token);
	return decodeToken["user_id"].asString();
}

bool User::checkPassword( string user_id,string password ){
	Json::Value userDB = getDB()->getJSON(user_id);
	if (userDB.isMember("error")) return false;

	if(password.compare(StringUtils::passwordDecrypt(userDB["password"].toStyledString())))
		return true;

	return false;
}

Json::Value User::asJSON(){

	Json::Value user;
	user["id"] = id;
	user["full_name"] = full_name;
	user["first_name"] = first_name;
	user["last_name"] = last_name;
	user["description"] = description;
	user["email"] = email;
	user["date_of_birth"] = date_of_birth;
	user["profile_picture"] = profile_picture;

	user["skills"] = Skill::listToArray(skills);

	user["jobs"] = Job::listToArray(jobs);

	user["education"] = Education::listToArray(education);

	user["recommendations_received"] = Recommendation::listToArray(recommendations_received);

	return user;

}

User::~User() {

}

} /* namespace std */
