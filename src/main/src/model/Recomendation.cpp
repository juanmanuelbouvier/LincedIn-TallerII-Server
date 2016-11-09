#include <model/Recomendation.h>

namespace std {

Recomendation::Recomendation(string recommender, string text){
	this->recommender = recommender;
	this->text = text;
}

Json::Value Recomendation::toJson(){
	Json::Value rec;
	rec["recommender"] = recommender; // proximamente un objeto del usuario
	rec["text"] = text;

	return rec;
}

string Recomendation::getRecommender(){
	return recommender;
}

string Recomendation::getText(){
	return text;
}

Recomendation::~Recomendation() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
