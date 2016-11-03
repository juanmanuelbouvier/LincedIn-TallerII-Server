#ifndef SRC_MAIN_SRC_SERVICE_OBJECTS_JOB_H_
#define SRC_MAIN_SRC_SERVICE_OBJECTS_JOB_H_

namespace std {

class Job {
private:
	string date_from,date_to,company,position;
public:
	Job(string job_id);
	bool create(map<string,string> data);
	string getDateFrom();
	string getDateTo();
	string getCompany();
	string getPosition();
	void setDateFrom(string date);
	void setDateTo(string date);
	void setCompany(string company);
	void setPosition(string position);

	virtual ~Job();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_SERVICE_OBJECTS_JOB_H_ */
