#include <modeltest/RecommendationTest.h>
#include <model/Recommendation.h>
#include <TestHelper.h>
#include <utils/ErrorMessage.h>
#include <iostream>

using namespace std;

TEST(RecommendationTest, addRecommendation){
	TestHelper::settinUpTestModel();

	string idUser1 = "pe";
	string idUser2 = "yss";

	User user1 = TestHelper::createBasicUsers(idUser1);
	User user2 = TestHelper::createBasicUsers(idUser2);

	string text = "recomiendo a este user";

	ErrorMessage error = Recommendation::addRecommendation(idUser2,idUser1,text);

	EXPECT_FALSE(error);

	Json::Value recommendations = Recommendation::getRecommendation(idUser2);

	EXPECT_TRUE(recommendations.isMember(idUser1));
	EXPECT_EQ(recommendations[idUser1]["text"],text);

	Json::Value mostRecommendations = Recommendation::getUsersMostRecommendation(10);

	EXPECT_EQ(mostRecommendations.size(),1);
	Json::Value userMostRecomendation = mostRecommendations[0];
	EXPECT_EQ(userMostRecomendation["user_id"].asString(),idUser2);
}

TEST(RecommendationTest, ErrorRecommendation){
	TestHelper::settinUpTestModel();

	string idUser1 = "pe";
	string idUser2 = "yss";
	string idUser3 = "fme";

	User user1 = TestHelper::createBasicUsers(idUser1);
	User user2 = TestHelper::createBasicUsers(idUser2);
	User user3 = TestHelper::createBasicUsers(idUser3);

	string text = "recomiendo a este user";

	ErrorMessage error = Recommendation::addRecommendation(idUser1,idUser2,text);
	EXPECT_FALSE(error);

	error = Recommendation::addRecommendation(idUser1,idUser3,text);
	error = Recommendation::addRecommendation(idUser1,idUser3,text);
	EXPECT_TRUE(error);

	ErrorMessage error2 = Recommendation::addRecommendation(idUser3,idUser2,text);
	EXPECT_FALSE(error2);

	Json::Value recommendations = Recommendation::getArrayRecommendation(idUser1);

	EXPECT_EQ(recommendations.size(),2);

	Json::Value mostRecommendations = Recommendation::getUsersMostRecommendation(10);

	EXPECT_EQ(mostRecommendations.size(),3);

	Json::Value userMostRecomendation = mostRecommendations[0];
	EXPECT_EQ(userMostRecomendation["user_id"].asString(),idUser1);

	ErrorMessage errorRemove = Recommendation::removeRecommendation(idUser1,idUser3);
	EXPECT_FALSE(errorRemove);

	recommendations = Recommendation::getArrayRecommendation(idUser1);
	EXPECT_EQ(recommendations.size(),1);
}
