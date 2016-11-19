#include <model/Skill.h>
#include <list>
#include <services/SharedServerAPI/SharedServerAPI.h>
#include <exception/SkillException.h>
#include <services/Logger/Logger.h>
#include <iostream>

using namespace std;

Skill::Skill(string name) {
	SharedServerAPI shared;
	Json::Value skill = shared.getSkill(name);
	if (skill.isObject()  && skill.isMember("error")){
		Log("Skill.cpp::" + to_string(__LINE__) + ". Error on find skill en Shared Server " + skill["error"].asString() ,ERROR);
		throw SkillException("Error on create Skill");
	}
	this->name = skill["name"].asString();
	this->category = skill["category"].asString();
	this->description = skill["description"].asString();
}

Skill Skill::create(Json::Value data){

	ErrorMessage error = check(data);

	if (error){
		throw SkillException("Error on create Skill. " +error.summary());
	}

	SharedServerAPI shared;
	Json::Value res = shared.setSkill(
			data["name"].asString(),
			data["description"].asString(),
			data["category"].asString()
			);

	return (res.isObject()  && res.isMember("error")) ? throw SkillException("Error on create Skill") : Skill(data["name"].asString());

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
	SharedServerAPI shared;
	Json::Value skill = shared.getSkill(skill_id);
	if (skill.isObject()  && skill.isMember("error")){
		return false;
	}
	return true;
}

bool Skill::exist(Json::Value data){
	SharedServerAPI shared;
	if (!data.isMember("name") or !data.isMember("description") or !data.isMember("category"))
		return false;

	Json::Value skill = shared.getSkill(data["name"].asString());
	if (skill.isObject()  && skill.isMember("error")){
		return false;
	}

	if (skill == data)
		return true;

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

bool Skill::setName(string new_name){
	SharedServerAPI shared;
	bool state = false;
	Json::Value res = shared.updateSkill(name,new_name,description,category,"");
	if (res.isObject()  && res.isMember("ok")){
		name = new_name;
		state = true;
	}
	return state;
}

bool Skill::setDescription(string new_description){
	SharedServerAPI shared;
	bool state = false;
	Json::Value res = shared.updateSkill(name,"",new_description,category,"");
	if (res.isObject()  && res.isMember("ok")){
		description = new_description;
		state = true;
	}

	return state;
}

bool Skill::setCategory(string new_category){
	SharedServerAPI shared;
	bool state = false;
	Json::Value res = shared.updateSkill(name,"",description,category,new_category);
	if (res.isObject()  && res.isMember("ok")){
		category = new_category;
		state = true;
	}

	return state;
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

bool Skill::remove(){
	SharedServerAPI shared;
	Json::Value res = shared.deleteSkill(name,category);

	return res.isMember("error") ? false : true;
}

Skill::~Skill() {

}

