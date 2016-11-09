#include <model/Job.h>

using namespace std;

Job::Job(string date_since, string date_to, string company, string name_position){
	this->date_since= date_since,
	this->date_to = date_to;
	this->company = company;
	this->position = new JobPosition(name_position);

}

Job Job::create(string date_since, string date_to, string company, string name_position){

	JobPosition position = new JobPosition(name_position);
	if (position == nullptr){
		return nullptr;
	}

	//save in db

	return new Job(date_since,date_to,company,name_position);
}

Job::~Job() {
	delete position;
}

