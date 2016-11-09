#ifndef SRC_MAIN_HEADERS_MODEL_EDUCATION_H_
#define SRC_MAIN_HEADERS_MODEL_EDUCATION_H_

namespace std {

class Education {

private:
	string start_date,end_date,school_name,degree;
public:
	Education(string start, string end, string school, string degree);
	Json::Value toJSON();

	virtual ~Education();
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_MODEL_EDUCATION_H_ */
