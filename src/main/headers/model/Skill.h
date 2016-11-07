#ifndef SRC_MAIN_SRC_MODEL_SKILL_H_
#define SRC_MAIN_SRC_MODEL_SKILL_H_

#include <extern/json.h>
#include <string>
#include <map>

namespace std {

class Skill {
private:
	string name,category,description;
public:
	Skill(string skill_name);

	static map<string,string> check( Json::Value data );
	static Skill* create(Json::Value data);

	string getName();
	string getDescription();
	string getCategory();

	void setName(string new_name);
	void setDescription(string new_description);
	void setCategory(string new_category);

	virtual ~Skill();
};

} /* namespace std */

#endif /* SRC_MAIN_SRC_SERVICE_OBJECTS_SKILL_H_ */
