#ifndef SRC_MAIN_SRC_MODEL_JOBPOSITION_H_
#define SRC_MAIN_SRC_MODEL_JOBPOSITION_H_

namespace std {

class JobPosition {
private:
	string name,category,description;
public:
	JobPosition(string name);
	JobPosition create(Json::Value data);
	string getName();
	string getCategory();
	string getDescription();
	bool setName(string name);
	bool setCategory(string category);
	bool setDescription(string description);
	virtual ~JobPosition();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_MODEL_JOBPOSITION_H_ */
