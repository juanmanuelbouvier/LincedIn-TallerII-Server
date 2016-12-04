#ifndef SRC_MAIN_HEADERS_MODEL_EDUCATION_H_
#define SRC_MAIN_HEADERS_MODEL_EDUCATION_H_

#include <extern/json.h>
#include <list>

using namespace std;
/**
 * Education is member object of User who describe it.
 */
class Education {

private:
	string start_date,end_date,school_name,degree;
public:
	/**
	 * Create an education.
	 * @param Start of date of education (free type)
	 * @param End date of education (free type, may be empty)
	 * @param Name of school/university
	 * @param Description of degree
	 */
	Education(string start, string end, string school, string degree);

	/**
	 * Get an Education object as Json.
	 * @return Json Value who contains atributes of Education
	 */
	Json::Value asJSON();

	/**
	 * Check if you can create an education with Json Data.
	 * @param Json Value who contains education requiered data.
	 * @retun True if the data is valid
	 */
	static bool check(Json::Value data);

	/**
	 * Conver a list of Education of Json Array who contains Education
	 * @note It applies asJson for each Education.
	 * @return Json Array with educations as Json.
	 */
	static Json::Value listToArray(list<Education> education);

	virtual ~Education();
};

#endif /* SRC_MAIN_HEADERS_MODEL_EDUCATION_H_ */
