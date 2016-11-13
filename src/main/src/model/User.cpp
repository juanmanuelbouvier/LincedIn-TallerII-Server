#include <model/User.h>
#include <utils/JSONUtils.h>
#include <iostream>
#include <exception>
#include <exception/SkillException.h>

namespace std {

User User::create( Json::Value data ) {

	map<string,string> error = check(data);

	//Generate JSON and put in database
	return User("id");
}

User::User(string user_id) {

	//MOCK
	full_name = user_id;
	first_name = "Carlos";
	last_name = "Fontela";
	description = "El capo de la FIUBA";
	email =  user_id + "@lincedin.com";
	date_of_birth = "1964-04-12 16:22:00";
	profile_picture = "https://cysingsoft.files.wordpress.com/2009/01/carlosfontela6.jpg?w=450";

	try
	  {
		Skill java = Skill("Java");
		skills.push_back(java);
		Skill c = Skill("c");
		skills.push_back(c);
	  }
	  catch (SkillException& e)
	  {
	    cout << "An exception occurred. " << e.what() << '\n';
	  }


	//jobs = Json::arrayValue;
	//user["jobs"].append(_createJob("2010-10-25 16:22:00","2011-10-25 16:22:00","Totos","Gerente comercial"));
	//user["jobs"].append(_createJob("2012-10-25 16:22:00","2016-10-25 16:22:00","FIUBA","Profesor"));
	//user["jobs"].append(_createJob("2016-10-25 17:22:00","","FIUBA","Buscando ser el director del depto de computación."));

	//user["education"] = Json::arrayValue;
	//user["education"].append(_createEducation("1981-03-12 16:22:00","1990-12-12 23:22:00","FIUBA","Ingeniero en casi todo"));

	//Json::Value recommendations_received(Json::arrayValue);
	//user["recommendations_received"] = Json::arrayValue;
	//user["recommendations_received"].append(_createRecomendation("Nico Paez", "Éste es un crack, se auto cita en las diapos."));

	/*
	//Levantar de la base de datos
	Json::Value userDB; // = db().open();getJSON(user_id)
	id = userDB["id"];
	first_name = userDB["first_name"];
	last_name = userDB["last_name"];
	full_name = first_name + " " + full_name;
	id = user_id;
	description = userDB["description"];
	date_of_birth = userDB["date_of_birth"];
	email = userDB["email"];
	profile_picture = userDB["profile_picture"];
	*/
}

map<string,string> User::check(Json::Value data){
	map<string,string> error;
	return error;
}

bool User::exist(string user_id){
	return true;
}

Json::Value User::asJSON(){

	Json::Value user;
	user["full_name"] = id;
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
