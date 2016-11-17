#ifndef SRC_MAIN_SRC_MODEL_SKILL_H_
#define SRC_MAIN_SRC_MODEL_SKILL_H_

#include <extern/json.h>
#include <string>
#include <utils/ErrorMessage.h>
#include <list>

using namespace std;

class Skill{
private:
	string name,category,description;
public:
	Skill(string skill_name);

	static ErrorMessage check( Json::Value data );
	static Skill create(Json::Value data);
	static bool exist(string skill_id);
	static bool exist(Json::Value data);

	string getName();
	string getDescription();
	string getCategory();

	bool setName(string new_name);
	bool setDescription(string new_description);
	bool setCategory(string new_category);

	Json::Value asJSON();

	static Json::Value listToArray(list<Skill> skills);

	virtual ~Skill();
};

#endif /* SRC_MAIN_SRC_SERVICE_OBJECTS_SKILL_H_ */
