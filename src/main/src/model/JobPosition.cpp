#include <model/JobPosition.h>

namespace std {

JobPosition::JobPosition(string name) {
	Json::Value job = SharedServerAPI::getInstance()->getJobPosition(name);
	if (job["error"]){
		return;
	}
	this->name = job["name"];
	this->category = job["category"];
	this->description = job["description"];
}

JobPosition JobPosition::create(Json::Value data){
	//check(data);
	Json::Value res = SharedServerAPI::getInstance()->setJobPosition(
			data["name"].asString(),
			data["description"].asString(),
			data["category"].asString()
			);

	if (!res["error"]){
		return JobPosition(data["name"].asString());
	}
	return nullptr;
}
string JobPosition::getName(){
	return name;
}
string JobPosition::getDescription(){
	return description;
}
string JobPosition::getCategory(){
	return category;
}

bool JobPosition::setName(string new_name){
	Json::Value res = SharedServerAPI::getInstance()->updateJobPosition(new_name,description,category);
	if (! res["error"]){
		name = new_name;
		return true;
	}

	return false;
}

bool JobPosition::setDescription(string new_description){
	Json::Value res = SharedServerAPI::getInstance()->updateJobPosition(new_description,description,category);
	if (! res["error"]){
		description = new_description;
		return true;
	}

	return false;
}

bool JobPosition::setCategory(string new_category){

	Json::Value res = SharedServerAPI::getInstance()->updateJobPosition(description,description,new_category);
	if (! res["error"]){
		category = new_category;
		return true;
	}

	return false;
}

JobPosition::~JobPosition() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
