#include <model/Skill.h>
#include <list>

namespace std {

Skill::Skill(string name) {
	Json::Value skill = SharedServerAPI::getInstance()->getSkill(name);
	if (skill["error"]){
		return;
	}
	this->name = skill["name"];
	this->category = skill["category"];
	this->description = skill["description"];
}

Skill Skill::create(Json::Value data){

	//check(data);

	Json::Value res = SharedServerAPI::getInstance()->setSkill(
			data["name"].asString(),
			data["description"].asString(),
			data["category"].asString()
			);

	if (!res["error"]){
		return Skill(data["name"].asString());
	}
	return nullptr;
}

map<string,string> Skill::check( Json::Value data ) {
	map<string,string> errors;
	list<string> dataExpected = {"name","description","category"};
	for (int i = 0; i < dataExpected.size(); i++) {
		string expected = dataExpected[i];
		if ( data[expected] ) {
			if (!data[expected].isString()) {
				errors[expected] = "Invalid value of " + expected;
			}
		} else {
			errors[expected] = expected + " not found in data";
		}
	}
	return errors;
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

bool Skill::setName(string new_name){
	Json::Value res = SharedServerAPI::getInstance()->updateSkill(new_name,description,category);
	if (! res["error"]){
		name = new_name;
		return true;
	}

	return false;
}

bool Skill::setDescription(string new_description){
	Json::Value res = SharedServerAPI::getInstance()->updateSkill(name,new_description,category);
	if (! res["error"]){
		description = new_description;
		return true;
	}

	return false;
}

bool Skill::setCategory(string new_category){

	Json::Value res = SharedServerAPI::getInstance()->updateSkill(name,description,new_category);
	if (! res["error"]){
		category = new_category;
		return true;
	}

	return false;
}

Skill::~Skill() {

}

} /* namespace std */
