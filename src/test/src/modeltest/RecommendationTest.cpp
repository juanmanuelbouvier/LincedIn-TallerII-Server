#include <modeltest/RecommendationTest.h>
#include <model/Recommendation.h>

using namespace std;

TEST(RecommendationTest, RecommendationAsJSON){
	string recommender = "Juan Manue";
	string text = "Este es bueno.";
	int timestamp = 123456789;

	Recommendation* recommendation = new Recommendation(recommender,text,timestamp);

	Json::Value json = recommendation->asJSON();

	EXPECT_EQ(recommender,json["recommender"].asString());
	EXPECT_EQ(recommender,recommendation->getRecommender());

	EXPECT_EQ(text,json["text"].asString());
	EXPECT_EQ(text,recommendation->getText());

	EXPECT_EQ(timestamp,json["timestamp"].asInt());
	EXPECT_EQ(timestamp,recommendation->getTimestamp());

	delete recommendation;
}

TEST(RecommendationTest, RecommendationListAsJSON){
	string recommender = "Juan Manuel";
	string text = "Este es bueno.";

	list<Recommendation> recommendations;

	Recommendation rec1 = Recommendation(recommender,text,123456);
	Recommendation rec2 = Recommendation(recommender,text,123459);

	recommendations.push_back(rec1);
	recommendations.push_back(rec2);

	Json::Value listOriginal = Json::Value(Json::arrayValue);
	listOriginal.append(rec1.asJSON());
	listOriginal.append(rec2.asJSON());

	Json::Value list = Recommendation::listToArray(recommendations);

	EXPECT_EQ(list,listOriginal);
}

