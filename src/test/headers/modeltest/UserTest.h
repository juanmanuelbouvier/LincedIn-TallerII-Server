#ifndef SRC_TEST_SRC_MODELTEST_USERTEST_H_
#define SRC_TEST_SRC_MODELTEST_USERTEST_H_
#include <gtest/gtest.h>
namespace std {

class UserTest  : public ::testing::Test{
public:
	static void settinUpDBFolderForModel();
	UserTest();
	virtual ~UserTest();
};

} /* namespace std */

#endif /* SRC_TEST_SRC_MODELTEST_USERTEST_H_ */
