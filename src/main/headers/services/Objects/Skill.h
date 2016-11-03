#ifndef SRC_MAIN_SRC_SERVICE_OBJECTS_SKILL_H_
#define SRC_MAIN_SRC_SERVICE_OBJECTS_SKILL_H_

namespace std {

class Skill {
private:
	SharedServerAPI* sharedServerAPI;
	string name,category,description;
public:
	Skill(string skill_name);
	bool create(map<string,string> data);
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
