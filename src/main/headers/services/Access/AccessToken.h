#ifndef SRC_MAIN_SRC_SERVICE_ACCESS_ACCESSTOKEN_H_
#define SRC_MAIN_SRC_SERVICE_ACCESS_ACCESSTOKEN_H_

#include <extern/json.h>
#include <jwt.h>
#include <string>

using namespace std;

class AccessToken {
private:
	static const char* KEY;
	static const jwt_alg_t ALGORITHM;
public:
	AccessToken(){};

	static Json::Value decode( string token );
	static string encode( Json::Value json );

	virtual ~AccessToken(){};
};

#endif /* SRC_MAIN_SRC_SERVICE_ACCESS_ACCESSTOKEN_H_ */
