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
		error.addError("add recommendation",recommender_id + " ya recomendó al usuario " + user_id);
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
		Json::Value old_cant = getDB()->getJSON(to_string(count));
		old_cant.removeMember(user_id);
	}

	Json::Value cant = getDB()->getJSON(new_count);
	cant[user_id] = new_count;
	getDB()->storeJSON(user_id,cant);

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
	//TODO buscar cantidad. y formatear eso
	return getCountDB()->getHigherKeyValue();
}



