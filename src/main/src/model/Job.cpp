#include <model/Job.h>
#include <exception/JobException.h>

using namespace std;

Job::Job(string date_since, string date_to, string company, string name_position) {
	this->date_since= date_since,
	this->date_to = date_to;
	this->company = company;
	this->position = new JobPosition(name_position);
}

Job Job::create(string date_since, string date_to, string company, string name_position){

	//buscar si existe el JobPosition
	JobPosition* position = new JobPosition(name_position);
	if (position == nullptr){
		throw new JobException("Error on create Job, not find JobPosition: " + name_position);
	}

	//save in db

	return Job(date_since,date_to,company,name_position);
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
