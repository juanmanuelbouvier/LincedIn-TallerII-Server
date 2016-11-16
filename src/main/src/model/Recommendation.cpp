#include <model/Recommendation.h>

using namespace std;

Recommendation::Recommendation(string recommender, string text, int timestamp){
	this->recommender = recommender;
	this->text = text;
	this->timestamp = timestamp;
}

Json::Value Recommendation::asJSON(){
	Json::Value rec;
	rec["recommender"] = recommender; // proximamente un objeto del usuario
	rec["text"] = text;
	rec["timestamp"] = timestamp;

	return rec;
}

string Recommendation::getRecommender(){
	return recommender;
}

string Recommendation::getText(){
	return text;
}

int Recommendation::getTimestamp(){
	return timestamp;
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
