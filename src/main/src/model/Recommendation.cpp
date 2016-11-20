#include <model/Recommendation.h>
#include <utils/DateUtils.h>

#define RECOMMENDATION_DB "Recommendations"
#define RECOMMENDATION_COUNT "CountRecommendations"

using namespace std;

DB* Recommendation::getDB(){
	return DBManager::getDB(RECOMMENDATION_DB);
}

DB* Recommendation::getCountDB(){
	return DBManager::getDB(RECOMMENDATION_COUNT);
}

Json::Value Recommendation::getUserRecommendations(string user_id){
	if (getDB()->exist(user_id)){
		return getDB()->getJSON(user_id);
	}

	Json::Value recommendations;
	getDB()->storeJSON(user_id,recommendations);
	return recommendations;
}

ErrorMessage Recommendation::addRecommendation(string user_id,string recommender_id,string text){
	ErrorMessage error;

	Json::Value user_recommendations = getUserRecommendations(user_id);

	if (user_recommendations.isMember(recommender_id)){
		error.addError("add recommendation",user_id + " already recommended by the user " + recommender_id);
		return error;
	}

	int count = user_recommendations.getMemberNames().size();

	Json::Value recommendation;
	recommendation["text"] = text;
	recommendation["timestamp"] = DateUtils::timestamp();

	user_recommendations[recommender_id] = recommendation;

	getDB()->storeJSON(user_id,user_recommendations);

	string new_count = "1";
	if (count > 0){
		new_count = to_string(count + 1);
		Json::Value old_cant = getCountDB()->getJSON(to_string(count));
		old_cant.removeMember(user_id);
		getCountDB()->storeJSON(to_string(count),old_cant);
	}

	Json::Value cant = getDB()->getJSON(new_count);
	cant[user_id] = new_count;
	getCountDB()->storeJSON(new_count,cant);

	return error;
}

ErrorMessage Recommendation::removeRecommendation(string user_id,string recommender_id){
	ErrorMessage error;

	Json::Value user_recommendations = getUserRecommendations(user_id);

	if (!user_recommendations.isMember(recommender_id)){
		error.addError("not exist recommendation",user_id + " no recommended by the user " + recommender_id);
		return error;
	}

	int count = user_recommendations.getMemberNames().size();

	user_recommendations.removeMember(recommender_id);

	getDB()->storeJSON(user_id,user_recommendations);

	int new_count = count - 1;
	Json::Value old_cant = getDB()->getJSON(to_string(count));
	old_cant.removeMember(user_id);
	getDB()->storeJSON(to_string(count),old_cant);

	if (new_count > 0){
		Json::Value cant = getDB()->getJSON(to_string(new_count));
		cant[user_id] = new_count;
		getDB()->storeJSON(user_id,cant);
	}

	return error;
}

Json::Value Recommendation::getRecommendation(string user_id){
	return getDB()->getJSON(user_id);
}

Json::Value Recommendation::getArrayRecommendation(string user_id){
	Json::Value recommendations = getRecommendation(user_id);
	Json::Value array = Json::arrayValue;

	Json::Value::Members memberNames = recommendations.getMemberNames();
	for (string& mem : memberNames){
		Json::Value recom = recommendations[mem];
		Json::Value rec;
		rec["recommender"] = mem;
		rec["text"] = recom["text"];
		rec["timestamp"] = recom["timestamp"];
		array.append(rec);
	}

	return array;
}

Json::Value Recommendation::getUsersMostRecommendation(int cantUser){
	Json::Value mostRecommender = Json::arrayValue;
	int cantUserAppending = 0;
	bool moreRes = true;
	int index = 0;
	while ((cantUserAppending < cantUser) and moreRes){
		Json::Value userMostrecommender = getCountDB()->getHigherKeyValue(index);
		if (userMostrecommender.isMember("error")){
			moreRes = false;
			continue;
		}
		Json::Value::Members memberNames = userMostrecommender.getMemberNames();
		for (string& mem : memberNames){
			Json::Value recom = userMostrecommender[mem];
			Json::Value rec;
			rec["recommender"] = mem;
			rec["text"] = recom["text"];
			rec["timestamp"] = recom["timestamp"];
			mostRecommender.append(rec);
			cantUserAppending++;
		}
		index++;
	}

	return mostRecommender;
}



