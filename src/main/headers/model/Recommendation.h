#ifndef SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_
#define SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_

#include <services/DB/DBManager.h>
#include <extern/json.h>
#include <utils/ErrorMessage.h>
#include <list>

using namespace std;

class Recommendation{
private:
	static DB* getDB();
	static DB* getCountDB();
	static Json::Value getUserRecommendations(string user_id);
public:
	static Json::Value getRecommendation(string user_id);
	static Json::Value getArrayRecommendation(string user_id);
	static Json::Value getUsersMostRecommendation(int cantUser);
	static ErrorMessage addRecommendation(string user_id,string recommender_id,string text);

	virtual ~Recommendation();
};

#endif /* SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_ */
