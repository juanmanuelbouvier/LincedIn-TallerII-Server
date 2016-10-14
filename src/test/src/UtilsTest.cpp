#include <UtilsTest.h>

#include <utils/PathUtils.h>
#include <utils/StringUtils.h>
#include <utils/VectorUtils.h>
#include <utils/DateUtils.h>

#include <ctime>

#include <string>

using namespace std;

TEST(UtilsTest, getFolderOfFilePath) {
	string path = "hello/world/file.txt";
	string result = PathUtils::getFolderOfFilePath(path);
	EXPECT_EQ("hello/world", result);
}

TEST(UtilsTest, fakePathIsInvalid) {
	bool fakePath = PathUtils::isValidPath("fakepathintherepository/");
	EXPECT_FALSE(fakePath);
}

TEST(UtilsTest, createdPathIsValid) {
	//This work if the test are run with make in basedir project
	bool truePath = PathUtils::isValidPath("src/");
	EXPECT_TRUE(truePath);

	bool truePathNotEnd = PathUtils::isValidPath("src");
	EXPECT_TRUE(truePathNotEnd);
}

TEST(UtilsTest, splitPath) {
	string path = "hello/world/hi";
	vector<string> theSplitPath = StringUtils::splitString(path,"/");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, splitPathIgnoreEmpty) {
	string path = "hello//world/hi/";
	vector<string> theSplitPath = StringUtils::splitString(path,"/");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, splitPathWithSelectedPrefix) {
	string path = "hello~world~hi";
	vector<string> theSplitPath = StringUtils::splitString(path,"~");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, splitStringWithOutPrefix) {
	string path = "hello/world/hi";
	vector<string> theSplitPath = StringUtils::splitString(path,"~");

	vector<string> expectedSplit = {"hello/world/hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, joinVectorOfStrings) {
	vector<string> theVector1 = {"hello","world"};
	string expected1 = "hello-world";
	string expected2 = "hello world";

	EXPECT_EQ(expected1, VectorUtils::joinVector(theVector1,"-"));
	EXPECT_EQ(expected2, VectorUtils::joinVector(theVector1));

	vector<string> emptyVector;
	EXPECT_EQ("", VectorUtils::joinVector(emptyVector));

}

TEST(UtilsTest, variableSubPath) {
	string variable_path = ":path";
	EXPECT_TRUE( PathUtils::isVariableSubPath(variable_path) );

	string non_variable_path = "path";
	EXPECT_FALSE( PathUtils::isVariableSubPath(non_variable_path) );
}

TEST(UtilsTest, variablePathToKey) {
	string pathVariable = ":path";
	string keyVariable = PathUtils::variableSubPathToKey(pathVariable);

	string expectedKey = "path";
	string keyNonVariable = PathUtils::variableSubPathToKey(expectedKey);

	EXPECT_EQ(keyVariable,expectedKey);
	EXPECT_EQ(expectedKey,keyNonVariable);

}

TEST(UtilsTest, generateRegexPath) {
	string pathWithVariables = "/hello/:name/:surname";

	string theGeneratedRegex = PathUtils::generateRegexPath(pathWithVariables);

	string expectedRegex = "^\\/hello\\/([^\\/]+?)\\/([^\\/]+?)(?:\\/(?=$))?$";

	EXPECT_EQ(theGeneratedRegex,expectedRegex);

}

TEST(UtilsTest, matchPathWithRegexPath){
	string pathWithVariables = "/hello/:name/:surname";

	string testPath = "/hello/tomi_with a very large name and spaces/bert";
	EXPECT_TRUE( PathUtils::matchPathRegexp(testPath,pathWithVariables) );

	string testPathWithQuery = "/hello/tomi/bert?arg1=true";
	EXPECT_TRUE( PathUtils::matchPathRegexp(testPathWithQuery,pathWithVariables) );

	string testNoMatchPath1 = "/hello/tomi";
	string testNoMatchPath2 = "/hello/tomi/bert/a";

	EXPECT_FALSE( PathUtils::matchPathRegexp(testNoMatchPath1,pathWithVariables) );
	EXPECT_FALSE( PathUtils::matchPathRegexp(testNoMatchPath2,pathWithVariables) );


}

TEST(UtilsTest, integratedUsingRouteParse) {
	string pathWithVariables = "/hello/:name/:surname";

	string testPath = "/hello/tomi/bert";

	map<string,string> result = PathUtils::routerParser(testPath,pathWithVariables);

	EXPECT_EQ(result.size(), 3);
	EXPECT_EQ(result["_route"],testPath);
	EXPECT_EQ(result["name"],"tomi");
	EXPECT_EQ(result["surname"],"bert");

	string testNotValidPath = "/hello/tomi/";

	map<string,string> resultNotValid = PathUtils::routerParser(testNotValidPath,pathWithVariables);

	EXPECT_EQ(resultNotValid.size(), 1);
	EXPECT_EQ(resultNotValid["_route"],testNotValidPath);

	string testPathWithQuery = "/hello/antonio/banderas?pelicula=elZorro";

	map<string,string> resultWithQuery = PathUtils::routerParser(testPathWithQuery,pathWithVariables);

	EXPECT_EQ(resultWithQuery.size(), 4);
	EXPECT_EQ(resultWithQuery["_route"],"/hello/antonio/banderas");
	EXPECT_EQ(resultWithQuery["name"],"antonio");
	EXPECT_EQ(resultWithQuery["surname"],"banderas");
	EXPECT_EQ(resultWithQuery["_query"],"pelicula=elZorro");

}

TEST(UtilsTest, DuummyGetTime) {
	string date = DateUtils::getTimeWithFormat("[%Y]");

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	string expectedYear = to_string(1900 + timePtr->tm_year);

	EXPECT_EQ(date,"[" + expectedYear + "]");

}

