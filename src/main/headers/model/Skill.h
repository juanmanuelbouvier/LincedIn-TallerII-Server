#ifndef SRC_MAIN_SRC_MODEL_SKILL_H_
#define SRC_MAIN_SRC_MODEL_SKILL_H_

#include <extern/json.h>
#include <string>
#include <utils/ErrorMessage.h>
#include <list>

using namespace std;
/**
 * Skill class wrap/represent an skill of Shared Server
 */
class Skill{
private:
	string name,category,description;
public:
	/**
	 * Get skill from name
	 * @param name of skill
	 * @note if the name not exist, throw an exception
	 */
	Skill(string skill_name);

	/**
	 * Check if an skill could be created with Json Data.
	 * @param Data of skill
	 * @return Error Summary who contain errors, if exist.
	 */
	static ErrorMessage check( Json::Value data );

	/**
	 * Create skill in shared server from data.
	 * @param Data of skill
	 * @return Created Skill.
	 * @note if Json data is invalid. Throw an exception
	 */
	static Skill create(Json::Value data);

	/**
	 * Check if skill exist from id
	 * @param skill id
	 * @return True if skill id exist
	 */
	static bool exist(string skill_id);

	/**
	 * Check if skill data exist
	 * @param Json Value who contain skill data.
	 * @return True if skill exist
	 */
	static bool exist(Json::Value data);

	string getName();
	string getDescription();
	string getCategory();

	bool setName(string new_name);
	bool setDescription(string new_description);
	bool setCategory(string new_category);
	/**
	 * Remove skill from shared server
	 * @return True if could be removed
	 */
	bool remove();

	/**
	 * Get skill data as Json
	 * @return Json Value who contain skill data
	 */
	Json::Value asJSON();

	/**
	 * Convert List of skill objects to Json Array of skills data
	 * @param A list who contain skills
	 * @return Json Value who contain `asJson` for each skill
	 */
	static Json::Value listToArray(list<Skill> skills);

	virtual ~Skill();
};

#endif /* SRC_MAIN_SRC_SERVICE_OBJECTS_SKILL_H_ */
