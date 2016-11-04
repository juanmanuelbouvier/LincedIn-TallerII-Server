#include <model/JobPosition.h>

namespace std {

JobPosition::JobPosition(string job_id) {
	// TODO Find job by id in DB and create
	//Json::Value job = SharedServerAPI::getInstance()->getJobPosition(job_id);
	//this->position = job["name"];
	//this->date_to = job["category"];
	//this->date_since = job["description"];
}
JobPosition* JobPosition::create(Json::Value data){
	//TODO Create job in DB by data
	return false;
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
