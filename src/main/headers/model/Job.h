#ifndef SRC_MAIN_SRC_MODEL_JOB_H_
#define SRC_MAIN_SRC_MODEL_JOB_H_

#include <extern/json.h>
#include <model/JobPosition.h>
#include <list>
#include <utils/ErrorMessage.h>

using namespace std;

class Job{
private:
	string date_since,date_to,company;
	JobPosition* position;
public:
	Job(string date_since, string date_to, string company, string name_position);
	Job(string date_since, string date_to, string company, Json::Value position);
	static ErrorMessage check(Json::Value job);
	Json::Value asJSON();

	static Json::Value listToArray(list<Job> jobs);

	virtual ~Job();
};

#endif /* SRC_MAIN_SRC_MODEL_JOB_H_ */
