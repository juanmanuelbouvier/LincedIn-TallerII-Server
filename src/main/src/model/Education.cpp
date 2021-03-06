#include <model/Education.h>

using namespace std;

Education::Education(string start, string end, string school, string degree) {
	this->start_date = start;
	this->end_date = end;
	this->school_name = school;
	this->degree = degree;
}

Json::Value Education::asJSON(){
	Json::Value education;
	education["start_date"] = start_date;
	if (end_date != "" and !end_date.empty()){
		education["end_date"] = end_date;
	}
	education["school_name"] = school_name;
	education["degree"] = degree;

	return education;
}

Json::Value Education::listToArray(list<Education> education){
	Json::Value array = Json::Value(Json::arrayValue);
	for (Education& obj : education){
		array.append(obj.asJSON());
	}

	return array;
}

bool Education::check(Json::Value data){
	if (!data.isMember("start_date") or !data.isMember("school_name") or !data.isMember("degree"))
		return false;

	return true;
}

Education::~Education() {
	// TODO Auto-generated destructor stub
}
