#ifndef SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_
#define SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_

#include <extern/json.h>
#include <list>

namespace std {

class Recommendation{
private:
	string recommender,text;
	int timestamp;
public:
	Recommendation(string recommender, string text,int timestamp);
	Json::Value asJSON();
	string getRecommender();
	string getText();
	string getTimestamp();
	static Json::Value listToArray(list<Recommendation> recommendations);
	virtual ~Recommendation();
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_ */
