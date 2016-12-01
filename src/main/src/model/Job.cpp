#include <model/Job.h>
#include <exception/JobException.h>

using namespace std;

Job::Job(string date_since, string date_to, string company, Json::Value position_data) {
	if (!JobPosition::exist(position_data))
		throw JobException("Error on create job, position invalid");

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
	if (!job.isMember("date_since")) {
		error.addError("date_since","Not defined date_since");
	}

	//JobPosition
	if (job.isMember("position")){
		if (job["position"].isObject() and !JobPosition::exist(job["position"])){
			error.addError("position", "Position does not exist.");
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

