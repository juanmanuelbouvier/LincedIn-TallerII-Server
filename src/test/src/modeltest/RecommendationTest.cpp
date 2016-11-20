#include <modeltest/RecommendationTest.h>
#include <model/Recommendation.h>
#include <TestHelper.h>
#include <utils/ErrorMessage.h>

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
