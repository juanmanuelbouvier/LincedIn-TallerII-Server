#include <AccessTokenTest.h>

#include <utils/JSONUtils.h>
#include <services/Access/AccessToken.h>

TEST(AccessTokenTest, encodeDecodeData) {
	Json::Value tokenData;
	tokenData["user_id"] = "goku";
	tokenData["expires"] = 2030;

	string token = AccessToken::encode(tokenData);

	EXPECT_TRUE( token.length() > 0 );

	Json::Value data = AccessToken::decode(token);

	EXPECT_EQ(data["user_id"],"goku");
	EXPECT_EQ(data["expires"],2030);
}
