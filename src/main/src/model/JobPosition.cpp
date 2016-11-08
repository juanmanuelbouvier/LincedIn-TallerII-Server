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

void JobPosition::setName(string name){
	this->name = name;
	//TODO update in DB
}
void JobPosition::setDescription(string description){
	this->description = description;
	//TODO update in DB
}
void JobPosition::setCategory(string category){
	this->category = category;
	//TODO update in DB
}

JobPosition::~JobPosition() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
