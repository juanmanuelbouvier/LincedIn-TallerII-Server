#ifndef SRC_MAIN_SRC_MODEL_JOBPOSITION_H_
#define SRC_MAIN_SRC_MODEL_JOBPOSITION_H_

#include <extern/json.h>

namespace std {

class JobPosition{
private:
	string name,category,description;
public:
	JobPosition(string name);
	static JobPosition create(Json::Value data);
	static bool exist(string name_position);
	static bool exist(Json::Value data);
	string getName();
	string getCategory();
	string getDescription();
	bool setName(string name);
	bool setCategory(string category);
	bool setDescription(string description);
	bool delet();
	Json::Value asJSON();
	virtual ~JobPosition();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_MODEL_JOBPOSITION_H_ */
