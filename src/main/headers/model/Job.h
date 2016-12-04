#ifndef SRC_MAIN_SRC_MODEL_JOB_H_
#define SRC_MAIN_SRC_MODEL_JOB_H_

#include <extern/json.h>
#include <model/JobPosition.h>
#include <list>
#include <utils/ErrorMessage.h>

using namespace std;
/**
 * Job object contain a Job of user.
 */
class Job{
private:
	string date_since,date_to,company;
	JobPosition* position;
public:
	/**
	 * Create Job with specific data.
	 * @param since date (free type)
	 * @param date to (free type, may be empty)
	 * @param Company where the work is performed
	 * @param Position of the Job
	 */
	Job(string date_since, string date_to, string company, string name_position);

	/**
	 * Create Job with a new Job Position
	 * @note It is the same as the previous method but the position contains more data (Shared Server)
	 */
	Job(string date_since, string date_to, string company, Json::Value position);

	/**
	 * Check if Job can be created with data
	 * @param Job data (date_since, position, etc)
	 * @return Error Summary with erros (if exist any)
	 */
	static ErrorMessage check(Json::Value job);

	/**
	 * Return Job data as Json
	 * @return Json Value who contains Job data.
	 */
	Json::Value asJSON();

	/**
	 * Conver a list of Job of Json Array who contains Education
	 * @note It applies asJson for each Job.
	 * @return Json Array with educations as Json.
	 */
	static Json::Value listToArray(list<Job> jobs);

	virtual ~Job();
};

#endif /* SRC_MAIN_SRC_MODEL_JOB_H_ */
