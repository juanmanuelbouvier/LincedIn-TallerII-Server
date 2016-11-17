#include <model/Job.h>
#include <exception/JobException.h>

using namespace std;

Job::Job(string date_since, string date_to, string company, Json::Value position_data) {
	if (!JobPosition::exist(position_data))
		throw JobException("error on create job, position invalid");

	this->date_since= date_since,
	this->date_to = date_to;
	this->company = company;
	this->position = new JobPosition(position_data["name"].asString());
}

Job::Job(string date_since, string date_to, string company, string name_position) {
	this->date_since= date_since,
	this->date_to = date_to;
	this->company = company;
	this->position = new JobPosition(name_position);
}

ErrorMessage Job::check(Json::Value job){
	ErrorMessage error;
	//date_since
	if (job.isMember("date_since")){
		//TODO check correct format
	} else {
		error.addError("date_since","not defined date_since");
	}

	//date_to
	if (job.isMember("date_to")){
		//TODO check correct format
	}

	//JobPosition
	if (job.isMember("name_position")){
		if (!JobPosition::exist(job["name_position"].toStyledString())){
			error.addError("name_position", "Position does not exist.");
		}
	}

	return error;
}

Json::Value Job::asJSON(){
	Json::Value job;

	job["date_since"] = date_since;
	job["date_to"] = date_to;
	job["company"] = company;
	job["position"] = position->asJSON();

	return job;
}

Json::Value Job::listToArray(list<Job> jobs){
	Json::Value array = Json::Value(Json::arrayValue);
	for (Job& obj : jobs){
		array.append(obj.asJSON());
	}

	return array;
}


Job::~Job() {
}

