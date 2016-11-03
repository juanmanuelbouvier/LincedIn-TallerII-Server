#include <services/Objects/Job.h>

namespace std {

Job::Job(string job_id) {
	// TODO Find job by id in DB and create
}
bool Job::create(map<string,string> data){
	//TODO Create job in DB by data
	return false;
}
string Job::getDateFrom(){
	return date_from;
}
string Job::getDateTo(){
	return date_to;
}
string Job::getCompany(){
	return company;
}
string Job::getPosition(){
	return position;
}
void Job::setDateFrom(string date){
	date_from = date;
	//TODO update in DB
}
void Job::setDateTo(string date){
	date_to = date;
	//TODO update in DB
}
void Job::setCompany(string company){
	this->company = company;
	//TODO update in DB
}
void Job::setPosition(string position){
	this->position = position;
	//TODO update in DB
}

Job::~Job() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
