#include <model/Recommendation.h>

namespace std {

Recommendation::Recommendation(string recommender, string text){
	this->recommender = recommender;
	this->text = text;
}

Json::Value Recommendation::asJSON(){
	Json::Value rec;
	rec["recommender"] = recommender; // proximamente un objeto del usuario
	rec["text"] = text;

	return rec;
}

string Recommendation::getRecommender(){
	return recommender;
}

string Recommendation::getText(){
	return text;
}

Json::Value Recommendation::listToArray(list<Recommendation> recommendations){
	Json::Value array = Json::Value(Json::arrayValue);
	for (Recommendation& obj : recommendations){
		array.append(obj.asJSON());
	}

	return array;
}


Recommendation::~Recommendation() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
