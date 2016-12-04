#ifndef SRC_MAIN_HEADERS_EXCEPTION_DBMANAGEREXCEPTION_H_
#define SRC_MAIN_HEADERS_EXCEPTION_DBMANAGEREXCEPTION_H_

#include <exception/AppServerException.h>

using namespace std;

class DBManagerException : public AppServerException {
public:
	DBManagerException(string msg) : AppServerException(msg){};
	virtual ~DBManagerException(){};
};

#endif /* SRC_MAIN_HEADERS_EXCEPTION_DBMANAGEREXCEPTION_H_ */
