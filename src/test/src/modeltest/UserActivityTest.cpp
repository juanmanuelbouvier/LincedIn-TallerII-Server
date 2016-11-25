#include <modeltest/UserActivityTest.h>
#include <model/UserActivity.h>
#include <TestHelper.h>
#include <utils/ErrorMessage.h>
#include <utils/DateUtils.h>

using namespace std;

TEST(UserAcrivityTest, registerAccess){

	TestHelper::settinUpTestModel();

	string id = "fme";

	User user = TestHelper::createBasicUsers(id);

	int timestamp = DateUtils::timestamp();

	ErrorMessage error = UserActivity::recordAccess(id);

	EXPECT_FALSE(error);

	int now = DateUtils::timestamp();

	int lastAccess = UserActivity::getLastAccessTimestamp(id);

	EXPECT_GE(lastAccess,timestamp);
	EXPECT_LE(lastAccess,now);

}

TEST(UserAcrivityTest, UserOnline){

	TestHelper::settinUpTestModel();

	string id = "fme";

	User user = TestHelper::createBasicUsers(id);

	UserActivity::recordAccess(id);

	EXPECT_TRUE(UserActivity::isOnline(id));
	EXPECT_FALSE(UserActivity::isOnline("tab"));
}
