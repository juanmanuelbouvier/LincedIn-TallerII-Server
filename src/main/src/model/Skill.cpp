#include <model/Skill.h>

namespace std {

Skill::Skill(string name) {
	sharedServerAPI = new SharedServerAPI();

	// TODO find
}

bool Skill::create(map<string,string> data){
	//TODO create in shared server
	return false;
}
string Skill::getName(){
	return name;
}

string Skill::getDescription(){
	return description;
}

string Skill::getCategory(){
	return category;
}

void Skill::setName(string new_name){
	//TODO update in sharedServer
	name = new_name;
}
void Skill::setDescription(string new_description){
	//TODO update in sharedServer
	description = new_description;
}

void Skill::setCategory(string new_category){
	//TODO update in sharedServer
	category = new_category;
}

Skill::~Skill() {

}

} /* namespace std */
