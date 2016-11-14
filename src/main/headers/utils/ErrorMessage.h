#ifndef SRC_MAIN_HEADERS_UTILS_ERRORMESSAGE_H_
#define SRC_MAIN_HEADERS_UTILS_ERRORMESSAGE_H_

#include <string>
#include <map>

namespace std {

class ErrorMessage {
private:
	map<string,string> error;
public:
	ErrorMessage();
	string summary();
	void addError(string key, string error);
	string getError(string key);
	bool empty();
	virtual ~ErrorMessage();
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_UTILS_ERRORMESSAGE_H_ */
