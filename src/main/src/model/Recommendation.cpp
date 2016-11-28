#include <model/Recommendation.h>
#include <utils/DateUtils.h>

#include <iostream>

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
	recommendations["received_recommendations"];
	recommendations["sent_recommendations"];
	getDB()->storeJSON(user_id,recommendations);
	return recommendations;
}

Json::Value Recommendation::getArraySentRecommendations(string user_id){
	if (!getDB()->exist(user_id)){
		return Json::arrayValue;
	}

	Json::Value recommendations = getDB()->getJSON(user_id);
	Json::Value sent_recommendations = recommendations["sent_recommendations"];
	Json::Value arraySentRecommendations = Json::arrayValue;

	Json::Value::Members memberNames = sent_recommendations.getMemberNames();
	for (string& mem : memberNames){
		Json::Value recom = sent_recommendations[mem];
		Json::Value rec;
		rec["user_id"] = mem;
		rec["text"] = recom["text"];
		rec["timestamp"] = recom["timestamp"];
		arraySentRecommendations.append(rec);
	}

	return arraySentRecommendations;
}

ErrorMessage Recommendation::addRecommendation(string user_id,string recommender_id,string text){
	ErrorMessage error;

	Json::Value user_recommendations = getUserRecommendations(user_id);
	Json::Value received_recommendations = user_recommendations["received_recommendations"] ;

	Json::Value recommender_recommendations = getUserRecommendations(recommender_id);
	Json::Value sent_recommendations = recommender_recommendations["sent_recommendations"];

	if (user_id == recommender_id){
		error.addError("add recommendation","Cannot recommender yourself");
		return error;
	}

	if (received_recommendations.isMember(recommender_id)){
		error.addError("add recommendation",user_id + " already recommended by the user " + recommender_id);
		return error;
	}

	int count = received_recommendations.getMemberNames().size();

	Json::Value recommendation;
	recommendation["text"] = text;
	recommendation["timestamp"] = DateUtils::timestamp();

	received_recommendations[recommender_id] = recommendation;
	sent_recommendations[user_id] = recommendation;

	user_recommendations["received_recommendations"] = received_recommendations;
	getDB()->storeJSON(user_id,user_recommendations);

	recommender_recommendations["sent_recommendations"] = sent_recommendations;
	getDB()->storeJSON(recommender_id,recommender_recommendations);

	string new_count = "1";
	if (count > 0){
		new_count = to_string(count + 1);
		Json::Value old_cant = getCountDB()->getJSON(to_string(count));
		old_cant.removeMember(user_id);
		getCountDB()->storeJSON(to_string(count),old_cant);
	}

	Json::Value cant;
	if (getCountDB()->exist(new_count)){
		cant = getCountDB()->getJSON(new_count);
	}
	cant[user_id] = new_count;
	getCountDB()->storeJSON(new_count,cant);

	return error;
}

ErrorMessage Recommendation::removeRecommendation(string user_id,string recommender_id){
	ErrorMessage error;

	Json::Value user_recommendations = getUserRecommendations(user_id);
	Json::Value received_recommendations = user_recommendations["received_recommendations"];

	if (!received_recommendations.isMember(recommender_id)){
		error.addError("not exist recommendation",user_id + " no recommended by the user " + recommender_id);
		return error;
	}

	int count = received_recommendations.getMemberNames().size();

	received_recommendations.removeMember(recommender_id);

	user_recommendations["received_recommendations"] = received_recommendations;
	getDB()->storeJSON(user_id,user_recommendations);

	int new_count = count - 1;
	Json::Value old_cant = getCountDB()->getJSON(to_string(count));
	old_cant.removeMember(user_id);
	getCountDB()->storeJSON(to_string(count),old_cant);

	if (new_count > 0){

		Json::Value cant;
		if (getCountDB()->exist(to_string(new_count))){
			cant = getCountDB()->getJSON(to_string(new_count));
		}
		cant[user_id] = new_count;
		getCountDB()->storeJSON(user_id,cant);
	}

	Json::Value recommender_recommendations = getUserRecommendations(recommender_id);
	Json::Value sent_recommendations = recommender_recommendations["sent_recommendations"];

	sent_recommendations.removeMember(user_id);
	recommender_recommendations["sent_recommendations"] = sent_recommendations;
	getDB()->storeJSON(recommender_id,recommender_recommendations);

	return error;
}

Json::Value Recommendation::getRecommendation(string user_id){
	return getUserRecommendations(user_id);
}

Json::Value Recommendation::getArrayReceivedRecommendations(string user_id){

	Json::Value user_recommendations = getUserRecommendations(user_id);
	Json::Value recommendations = user_recommendations["received_recommendations"];
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
			break;
		}
		Json::Value::Members memberNames = userMostrecommender.getMemberNames();
		for (string& mem : memberNames){
			Json::Value rec;
			rec["user_id"] = mem;
			rec["count_recommendations"] = userMostrecommender[mem];
			mostRecommender.append(rec);
			cantUserAppending++;
		}
		index++;
	}

	return mostRecommender;
}


Json::Value Recommendation::getSentRecommendations(string user_id){
	Json::Value recommendations = getUserRecommendations(user_id);
	return recommendations["sent_recommendations"];
}

Json::Value Recommendation::getReceivedRecommendations(string user_id){
	Json::Value recommendations = getUserRecommendations(user_id);
	return recommendations["received_recommendations"];
}



