#ifndef SRC_TEST_SRC_MODELTEST_TESTHELPER_H_
#define SRC_TEST_SRC_MODELTEST_TESTHELPER_H_

#include <model/User.h>

using namespace std;

class TestHelper {
public:
	static User createBasicUsers(string id);
	static bool settinUpTestModel();
};

#endif /* SRC_TEST_SRC_MODELTEST_TESTHELPER_H_ */
