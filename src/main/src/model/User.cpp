#include <model/User.h>

namespace std {

User* User::create( map<string,string> data ) {
	//Generate JSON and put in database
	return new User("id");
}

User::User(string user_id) {
	//Levantar de la base de datos
	Json::Value userDB; // = db().open();getJSON(user_id)
	first_name = userDB["first_name"];
	last_name = userDB["last_name"];
	full_name = first_name + " " + full_name;
	id = user_id;
	description = userDB["description"];
	date_of_birth = userDB["date_of_birth"];
	email = userDB["email"];
	profile_picture = userDB["profile_picture"];

}

User::~User() {
}

} /* namespace std */
