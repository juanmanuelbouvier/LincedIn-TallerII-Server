#ifndef SRC_TEST_SRC_MODELTEST_GEOLOCALIZATIONTESTS_H_
#define SRC_TEST_SRC_MODELTEST_GEOLOCALIZATIONTESTS_H_

#include <gtest/gtest.h>
#include <string>
#include <model/User.h>


class GeolocalizationTests  : public ::testing::Test{
public:
	static void settinUpDBFolderForModel();
	static User createUser(std::string name);
	GeolocalizationTests();
	virtual ~GeolocalizationTests();
};

#endif /* SRC_TEST_SRC_MODELTEST_GEOLOCALIZATIONTESTS_H_ */
