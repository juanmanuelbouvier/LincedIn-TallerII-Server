#include <model/Skill.h>
#include <list>
#include <services/SharedServerAPI/SharedServerAPI.h>
#include <exception/SkillException.h>
#include <services/Logger/Logger.h>
#include <iostream>

namespace std {

Skill::Skill(string name) {
	Json::Value skill = SharedServerAPI::getInstance()->getSkill(name);
	if (skill.isObject()  && skill.isMember("error")){
		cout << Log("Skill.cpp::" + to_string(__LINE__) + ". Error on find skill en Shared Server " + skill["error"].asString() ,WARNING) << endl;
		throw new SkillException("Error on create Skill");
	}
	this->name = skill["name"].asString();
	this->category = skill["category"].asString();
	this->description = skill["description"].asString();
}

Skill Skill::create(Json::Value data){

	//check(data);

	Json::Value res = SharedServerAPI::getInstance()->setSkill(
			data["name"].asString(),
			data["description"].asString(),
			data["category"].asString()
			);

	if (res.isObject()  && res.isMember("error")){
		cout << Log("Skill.cpp::" + to_string(__LINE__) + ". Error on create skill in Shared Server " + res["error"].asString() ,WARNING) << endl;
		throw new SkillException("Error on create Skill");
	}
	return Skill(data["name"].asString());
}

ErrorMessage Skill::check( Json::Value data ) {
	ErrorMessage errors;
	list<string> dataExpected = {"name","description","category"};
	for (string& expected : dataExpected) {
		if ( data.isMember(expected)) {
			if (!data[expected].isString()) {
				errors.addError(expected,"Invalid value of " + expected);
			}
		} else {
			errors.addError(expected,expected + " not found in data");
		}
	}
	return errors;
}

bool Skill::exist(string skill_id){
	Json::Value skill = SharedServerAPI::getInstance()->getSkill(skill_id);
	if (skill.isObject()  && skill.isMember("error")){
		return false;
	}
	return true;
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
	if (res.isObject()  && res.isMember("error")){

		return false;
	}
	name = new_name;
	return true;
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

Json::Value Skill::asJSON(){
	Json::Value skill;
	skill["name"] = name;
	skill["description"] = description;
	skill["category"] = category;

	return skill;
}

Json::Value Skill::listToArray(list<Skill> skills){
	Json::Value array = Json::Value(Json::arrayValue);
	for (Skill& obj : skills){
		array.append(obj.asJSON());
	}

	return array;
}

Skill::~Skill() {

}

} /* namespace std */
