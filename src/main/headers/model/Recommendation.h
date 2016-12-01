#ifndef SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_
#define SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_

#include <services/DB/DBManager.h>
#include <extern/json.h>
#include <utils/ErrorMessage.h>
#include <list>

using namespace std;
/**
 * A user can
 */
class Recommendation {
private:
	static DB* getDB();
	static DB* getCountDB();
	static Json::Value getUserRecommendations(string user_id);
public:
	/**
	 * Get recomendations (sended and received) of user
	 * @param user id
	 * @return Json Value with recommendations.
	 */
	static Json::Value getRecommendation(string user_id);

	/**
	 * Add Recommendation
	 * @param user id who recommend
	 * @param user id who be recommended
	 * @param An optional test of recommendation
	 * @return Error Message with error, if exist any.
	 */
	static ErrorMessage addRecommendation(string user_id,string recommender_id,string text);

	/**
	 * Remove Recommendation
	 * @param user id who recommend
	 * @param user id who was recommended
	 * @return Error Message with error, if exist any.
	 */
	static ErrorMessage removeRecommendation(string user_id,string recommender_id);

	/**
	 * Get all sent recommendations of user
	 * @param user id
	 * @return All Recommendation who user id sent
	 */
	static Json::Value getArraySentRecommendations(string user_id);

	/**
	 * Get all received recommendations of user
	 * @param user id
	 * @return All Recommendation who user id received
	 */
	static Json::Value getArrayReceivedRecommendations(string user_id);

	static Json::Value getSentRecommendations(string user_id);
	static Json::Value getReceivedRecommendations(string user_id);

	/**
	 * Get tops users who received more recommendations
	 * @param Number of user to get
	 * @return Json Array with most reccomended users
	 */
	static Json::Value getUsersMostRecommendation(int cantUser);

	virtual ~Recommendation();
};

#endif /* SRC_MAIN_HEADERS_MODEL_RECOMMENDATION_H_ */
