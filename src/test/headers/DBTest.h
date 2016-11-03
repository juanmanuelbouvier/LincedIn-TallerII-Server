#ifndef SRC_TEST_DBTEST_H_
#define SRC_TEST_DBTEST_H_

#include <gtest/gtest.h>


class DBTest : public ::testing::Test {

protected:

    // You can do set-up work for each test here.
	DBTest();

    // You can do clean-up work that doesn't throw exceptions here.
	virtual ~DBTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

};

#endif /* SRC_TEST_DBTEST_H_ */