#include <model/User.h>
#include <model/Image.h>
#include <utils/JSONUtils.h>
#include <utils/DateUtils.h>
#include <utils/StringUtils.h>
#include <iostream>
#include <services/Logger/Logger.h>
#include <exception/SkillException.h>
#include <exception/UserException.h>
#include <exception/JobException.h>
#include <services/DB/DBs.h>

using namespace std;

DB* User::getDB(){
	return DBManager::getDB(Databases::DB_USER);
}


DB* User::getEmailDB(){
	return DBManager::getDB(Databases::DB_EMAIL);
}

User User::create( Json::Value data ) {

	ErrorMessage error = check(data);

	if (!error.empty()){
		Log("User.cpp::" + to_string(__LINE__) + ". Error on create skill, check data ",ERROR);
		throw UserException("Error on create user, check data. Summary: " + error.summary());
	}

	if (getEmailDB()->exist(data["email"].asString())){
		Log("User.cpp::" + to_string(__LINE__) + ". Email already exist.",ERROR);
		throw UserException("Email already exist.");
	}

	string user_id = generateUserID(data["id"].asString(),data["first_name"].asString(),data["last_name"].asString());

	Json::Value userDB;
	userDB["first_name"] = data["first_name"];
	userDB["last_name"] = data["last_name"];
	userDB["description"] = data["description"];
	userDB["email"] = data["email"];
	getEmailDB()->store(data["email"].asString(),user_id);
	userDB["date_of_birth"] = data["date_of_birth"];

	//firebase id
	string idFirebase = "";
	if (data.isMember("firebase_id")){
		idFirebase = data["firebase_id"].asString();
	}
	userDB["firebase_id"] = idFirebase;

	//imagen en base 64, guardar url
	if (data.isMember("profile_picture")){
		userDB["profile_picture"] = Image::urlByBase64(data["profile_picture"].asString());
	}

	userDB["skills"] = data["skills"];
	userDB["jobs"] = data["jobs"];
	userDB["education"] = data["education"];

	userDB["password"] = StringUtils::passwordEncrypt(data["password"].asString());
	int now = DateUtils::timestamp();
	userDB["register_timestamp"] = now;
	userDB["last_edit_timestamp"] =  now;

	return (getDB()->storeJSON(user_id, userDB)) ? User(user_id) : throw UserException("Error on store user in DB");

}

bool User::remove( string user_id){
	Json::Value data = getDB()->getJSON(user_id);
	if (data.isMember("error"))
		return false;

	if(getDB()->Delete(user_id)){
		getEmailDB()->Delete(data["email"].asString());
		Image::remove(data["profile_picture"].asString());
		return true;
	}

	return false;
}

ErrorMessage User::update(string user_id,Json::Value data){
	ErrorMessage error;
	Json::Value userDB = getDB()->getJSON(user_id);


	if (userDB.isMember("error")){
		error.addError("user_id","Not find user id in DB");
		return error;
	}

	if (!data.isMember("password")){
		data["password"] = userDB["password"];
	}


	ErrorMessage checkMessage = User::check(data);
	if (checkMessage) return checkMessage;

	//no public information
	data["register_timestamp"] = userDB["register_timestamp"].asInt();
	data["last_edit_timestamp"] = DateUtils::timestamp();

	if (data.isMember("profile_picture")){
		//booro imagen anterior
		Image::remove(userDB["profile_picture"].asString());
		data["profile_picture"] = Image::urlByBase64(data["profile_picture"].asString());
	}

	if (!getDB()->storeJSON(user_id,data)){
		error.addError(user_id,"Error on store data in DB");
	}

	if (data["email"] != userDB["email"]){
		getEmailDB()->Delete(userDB["email"].asString());
		getEmailDB()->store(data["email"].asString(),user_id);
	}

	return error;
}

User::User(string user_id) {

	Json::Value userDB = getDB()->getJSON(user_id);
	if (userDB.isMember("error")){
		Log("User.cpp::" + to_string(__LINE__) + ". Error on create user " + userDB["error"].asString() ,ERROR);
		throw UserException("User invalid.");
	}

	id = user_id;
	first_name = userDB["first_name"].asString();
	last_name = userDB["last_name"].asString();
	full_name = first_name + " " + last_name;
	description = userDB["description"].asString();
	email =  userDB["email"].asString();
	date_of_birth = userDB["date_of_birth"].asString();
	profile_picture = userDB["profile_picture"].asString();
	firebase_id = userDB["firebase_id"].asString();

	if (userDB.isMember("skills")){
		Json::Value skills_db = userDB["skills"];
		for( Json::ValueIterator itr = skills_db.begin() ; itr != skills_db.end() ; itr++ ) {
			Json::Value skill_data = skills_db[itr.index()];
			string skill_name = skill_data["name"].asString();
			try{
				Skill skill = Skill(skill_name);
				skills.push_back(skill);
			} catch (SkillException& e){
				Log("User.cpp::" + to_string(__LINE__) + ". create skill " + skill_name + ". " + e.what() ,ERROR);
				throw UserException("Error on create skill " + skill_name);
			}
		}
	}

	if (userDB.isMember("jobs")){
		Json::Value jobs_data = userDB["jobs"];
		for( Json::ValueIterator itr = jobs_data.begin() ; itr != jobs_data.end() ; itr++ ) {
			Json::Value job_data = jobs_data[itr.index()];
			Json::Value job_position_data = job_data["position"];
			try{
				Job job = Job(job_data["date_since"].asString(),job_data.get("date_to","").asString(),job_data["company"].asString(),job_data["position"]);
				jobs.push_back(job);
			} catch (JobException& e){
				Log("User.cpp::" + to_string(__LINE__) + ". create job. " + e.what() ,ERROR);
					throw UserException("Error on create Job");
			}
		}
	}

	if (userDB.isMember("education")){
		Json::Value education_data = userDB["education"];
		for( Json::ValueIterator itr = education_data.begin() ; itr != education_data.end() ; itr++ ) {
			Json::Value ed_data = education_data[itr.index()];
			Education ed = Education(ed_data["start_date"].asString(),ed_data.get("end_date","").asString(), ed_data["school_name"].asString(),ed_data["degree"].asString());
			education.push_back(ed);
		}
	}

}


string User::getID(){
	return this->id;
}

string User::getFullName(){
	return this->full_name;
}

string User::getFirebaseID(){
	return this->firebase_id;
}

ErrorMessage User::check(Json::Value data){
	ErrorMessage error;

	if (!data.isMember("id")){
		error.addError("id","Id not specified");
	}

	if (!data.isMember("password")){
		error.addError("password","Password not specified.");
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

	if (data.isMember("skills") and (data["skills"].size() > 0)){
		Json::Value skills = data["skills"];
		for( Json::ValueIterator itr = skills.begin() ; itr != skills.end() ; itr++ ) {
			Json::Value val = skills[itr.index()];
			if (! Skill::exist(val) ) {
				error.addError("skill","Skill invalid (" + val.toStyledString() + ").");
			}
		}
	}

	if (data.isMember("jobs") and (data["jobs"].size() > 0)){
		Json::Value jobs = data["jobs"];
		for( Json::ValueIterator itr = jobs.begin() ; itr != jobs.end() ; itr++ ) {
			Json::Value val = jobs[itr.index()];
			ErrorMessage error_job = Job::check(val);
			if (!error_job.empty()) {
				error.addError("Job","Job invalid (" + error_job.summary() + ").");
			}
		}
	}

	if (data.isMember("education") and (data["education"].size() > 0)){
		Json::Value educ = data["education"];
		for( Json::ValueIterator itr = educ.begin() ; itr != educ.end() ; itr++ ) {
			Json::Value val = educ[itr.index()];
			if (!Education::check(val)) {
				error.addError("Education","Education invalid (" + val.toStyledString() + ").");
			}
		}
	}
	return error;
}

bool User::exist(string user_id){

	return getDB()->exist(user_id);

}


string User::getIdByEmail(string email ){
	return getEmailDB()->get(email);
}

bool User::checkPassword( string user_id,string password ){
	Json::Value userDB = getDB()->getJSON(user_id);
	if (userDB.isMember("error")) return false;

	if(password == StringUtils::passwordDecrypt(userDB["password"].asString()))
		return true;

	return false;
}

string User::generateUserID(string candidate,string first_name, string last_name){
	if(!candidate.empty() and !getDB()->exist(candidate)){
		return candidate;
	}

	bool validUserId = false;
	int number = 0;
	string user_id;

	while (!validUserId){
		user_id = first_name.substr(0, 1) + last_name;
		if (number > 0){
			user_id += to_string(number);
		}
		if (!getDB()->exist(user_id)){
			validUserId = true;
		}
	}

	return user_id;
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
	user["firebase_id"] = firebase_id;

	user["skills"] = Skill::listToArray(skills);

	user["jobs"] = Job::listToArray(jobs);

	user["education"] = Education::listToArray(education);

	return user;

}

Json::Value User::getAllUsers(){
	return getDB()->getAllKeys();
}

string User::getFirebaseID(string id){
	if (!getDB()->exist(id))
		return "";
	return getDB()->getJSON(id)["firebase_id"].asString();
}

User::~User() {

}
