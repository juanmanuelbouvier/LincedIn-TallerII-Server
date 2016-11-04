#ifndef SRC_MAIN_SRC_MODEL_JOBPOSITION_H_
#define SRC_MAIN_SRC_MODEL_JOBPOSITION_H_

namespace std {

class JobPosition {
private:
	string name,category,description;
public:
	JobPosition(string job_id);
	JobPosition* create(Json::Value data);
	string getName();
	string getCategory();
	string getDescription();
	void setName(string name);
	void setCategory(string category);
	void setDescription(string description);
	virtual ~JobPosition();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_MODEL_JOBPOSITION_H_ */
