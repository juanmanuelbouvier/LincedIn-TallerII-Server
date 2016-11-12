#ifndef SRC_MAIN_HEADERS_MODEL_EDUCATION_H_
#define SRC_MAIN_HEADERS_MODEL_EDUCATION_H_

#include <extern/json.h>
#include <list>

namespace std {

class Education {

private:
	string start_date,end_date,school_name,degree;
public:
	Education(string start, string end, string school, string degree);
	Json::Value asJSON();

	static Json::Value listToArray(list<Education> education);
	virtual ~Education();
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_MODEL_EDUCATION_H_ */
