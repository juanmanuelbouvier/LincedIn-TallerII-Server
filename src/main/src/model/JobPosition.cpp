#include <model/JobPosition.h>
#include <services/SharedServerAPI/SharedServerAPI.h>

namespace std {

JobPosition::JobPosition(string name) {
	SharedServerAPI shared;
	Json::Value job = shared.getJobPosition(name);
	if ( job.isObject()  && job.isMember("error") ){
		return;
	}
	this->name = job["name"].asString();
	this->category = job["category"].asString();
	this->description = job["description"].asString();
}

JobPosition JobPosition::create(Json::Value data){
	SharedServerAPI shared;
	Json::Value res = shared.setJobPosition(
			data["name"].asString(),
			data["description"].asString(),
			data["category"].asString()
			);
	if (not (res.isObject()  && res.isMember("error"))){
		return JobPosition(data["name"].asString());
	}
	return JobPosition(data["name"].asString());
}

bool JobPosition::exist(string name_position){
	SharedServerAPI shared;
	Json::Value position = shared.getJobPosition(name_position);
	if (position.isObject() && position.isMember("error")){
		return false;
	}
	return true;
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
	SharedServerAPI shared;
	Json::Value res = shared.updateJobPosition(new_name,description,category);
	if (not (res.isObject()  && res.isMember("error"))){
		name = new_name;
		return true;
	}

	return false;
}

bool JobPosition::setDescription(string new_description){
	SharedServerAPI shared;
	Json::Value res = shared.updateJobPosition(new_description,description,category);
	if (not (res.isObject()  && res.isMember("error"))){
		description = new_description;
		return true;
	}

	return false;
}

bool JobPosition::setCategory(string new_category){
	SharedServerAPI shared;
	Json::Value res = shared.updateJobPosition(description,description,new_category);
	if (not (res.isObject()  && res.isMember("error"))){
		category = new_category;
		return true;
	}

	return false;
}

bool JobPosition::delet(){
	SharedServerAPI shared;
	Json::Value res = shared.deleteJobPosition(name,category);
	if (res.isMember("ok"))
		return true;
	return false;
}


Json::Value JobPosition::asJSON(){
	Json::Value job_position;
	job_position["name"] = name;
	job_position["description"] = description;
	job_position["category"] = category;

	return job_position;
}

JobPosition::~JobPosition() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
