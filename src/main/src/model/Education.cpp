#include <model/Education.h>

namespace std {

Education::Education(string start, string end, string school, string degree) {
	this->start_date = start;
	this->end_date = end;
	this->school_name = school;
	this->degree = degree;
}

Json::Value Education::toJSON(){
	Json::Value education;
	education["start_date"] = start_date;
	if (end_date != "" and end_date != nullptr){
		education["end_date"] = end_date;
	}
	education["school_name"] = school_name;
	education["degree"] = degree;

	return education;
}

Education::~Education() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
