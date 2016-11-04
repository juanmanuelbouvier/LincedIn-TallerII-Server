#include <model/Skill.h>

namespace std {

Skill::Skill(string name) {
	Json::Value skill = SharedServerAPI::getInstance()->getSkill(name);
	this->name = skill["name"];
	this->category = skill["category"];
	this->description = skill["description"];
}

Skill* Skill::create(Json::Value data){

	Json::FastWriter fastWriter;

	HTTPResponse* response = SharedServerAPI::getInstance()->setSkill(fastWriter.write(data["name"]),fastWriter.write(data["description"]),fastWriter.write(data["category"]));

	if (response->getCode() == 200){
		return Skill(data["name"]);
	}
	return nullptr;
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
