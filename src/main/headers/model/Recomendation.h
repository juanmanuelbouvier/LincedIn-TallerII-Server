#ifndef SRC_MAIN_HEADERS_MODEL_RECOMENDATION_H_
#define SRC_MAIN_HEADERS_MODEL_RECOMENDATION_H_

namespace std {

class Recomendation {
private:
	string recommender,text;
public:
	Recomendation(string recommender, string text);
	Json::Value toJson();
	string getRecommender();
	string getText();
	virtual ~Recomendation();
};

} /* namespace std */

#endif /* SRC_MAIN_HEADERS_MODEL_RECOMENDATION_H_ */
