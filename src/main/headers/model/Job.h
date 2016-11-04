#ifndef SRC_MAIN_SRC_MODEL_JOB_H_
#define SRC_MAIN_SRC_MODEL_JOB_H_

namespace std {

class Job {
private:
	string date_since,date_to,company;
	JobPosition* position;
public:
	Job();
	virtual ~Job();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_MODEL_JOB_H_ */
