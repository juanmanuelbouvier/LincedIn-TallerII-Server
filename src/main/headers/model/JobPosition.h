#ifndef SRC_MAIN_SRC_MODEL_JOBPOSITION_H_
#define SRC_MAIN_SRC_MODEL_JOBPOSITION_H_

#include <extern/json.h>

using namespace std;

/**
 * Job Position wrap/represent a job position type of shared Server.
 */
class JobPosition{
private:
	string name,category,description;
public:
	/**
	 * Get a job position from name.
	 * @param name of Job position
	 * @note Throw an exception if job position not exist.
	 */
	JobPosition(string name);

	/**
	 * Create Job Position in shared server with data.
	 * @param Job Position data.
	 * @return A created Job position
	 */
	static JobPosition create(Json::Value data);

	/**
	 * Check if job position name exist shared server
	 * @param name of job position
	 * @return True if exist.
	 */
	static bool exist(string name_position);

	/**
	 * Check if job position data exist in shared server
	 * @param data of job position
	 * @return True if exist.
	 */
	static bool exist(Json::Value data);

	/**
	 * Getters.
	 */
	string getName();
	string getCategory();
	string getDescription();

	/**
	 * Setters.
	 */
	bool setName(string name);
	bool setCategory(string category);
	bool setDescription(string description);

	bool remove();
	/**
	 * Get Job Position data as Json
	 * @return Json Value with data of Job Position
	 */
	Json::Value asJSON();

	virtual ~JobPosition();
};

#endif /* SRC_MAIN_SRC_MODEL_JOBPOSITION_H_ */
