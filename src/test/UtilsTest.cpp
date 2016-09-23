#include "UtilsTest.h"
#include <iostream>

using namespace std;


TEST(UtilsTest, getFolderOfFilePath) {
	string path = "hello/world/file.txt";
	string result = getFolderOfFilePath(path);
	EXPECT_EQ("hello/world", result);
}

TEST(UtilsTest, fakePathIsInvalid) {
	bool fakePath = isValidPath("fakepathintherepository/");
	EXPECT_FALSE(fakePath);
}

TEST(UtilsTest, createdPathIsValid) {
	//This work if the test are run with make in basedir project
	bool truePath = isValidPath("src/");
	EXPECT_TRUE(truePath);

	bool truePathNotEnd = isValidPath("src");
	EXPECT_TRUE(truePathNotEnd);
}

TEST(UtilsTest, splitPath) {
	string path = "hello/world/hi";
	vector<string> theSplitPath = splitString(path,"/");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, splitPathIgnoreEmpty) {
	string path = "hello//world/hi/";
	vector<string> theSplitPath = splitString(path,"/");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, splitPathWithSelectedPrefix) {
	string path = "hello~world~hi";
	vector<string> theSplitPath = splitString(path,"~");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, splitStringWithOutPrefix) {
	string path = "hello/world/hi";
	vector<string> theSplitPath = splitString(path,"~");

	vector<string> expectedSplit = {"hello/world/hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, joinVectorOfStrings) {
	vector<string> theVector1 = {"hello","world"};
	string expected1 = "hello-world";
	string expected2 = "hello world";

	EXPECT_EQ(expected1, joinVector(theVector1,"-"));
	EXPECT_EQ(expected2, joinVector(theVector1));

	vector<string> emptyVector;
	EXPECT_EQ("", joinVector(emptyVector));

}

TEST(UtilsTest, variableSubPath) {
	string variable_path = ":path";
	EXPECT_TRUE(isVariableSubPath(variable_path));

	string non_variable_path = "path";
	EXPECT_FALSE(isVariableSubPath(non_variable_path));
}

TEST(UtilsTest, variablePathToKey) {
	string pathVariable = ":path";
	string keyVariable = variableSubPathToKey(pathVariable);

	string expectedKey = "path";
	string keyNonVariable = variableSubPathToKey(expectedKey);

	EXPECT_EQ(keyVariable,expectedKey);
	EXPECT_EQ(expectedKey,keyNonVariable);

}

TEST(UtilsTest, generateRegexPath) {
	string pathWithVariables = "/hello/:name/:surname";

	string theGeneratedRegex = generateRegexPath(pathWithVariables);

	string expectedRegex = "^\\/hello\\/([^\\/]+?)\\/([^\\/]+?)(?:\\/(?=$))?$";

	EXPECT_EQ(theGeneratedRegex,expectedRegex);

}

TEST(UtilsTest, matchPathWithRegexPath){
	string pathWithVariables = "/hello/:name/:surname";

	string testPath = "/hello/tomi_with a very large name and spaces/bert";
	EXPECT_TRUE( matchPathRegexp(testPath,pathWithVariables) );

	string testPathWithQuery = "/hello/tomi/bert?arg1=true";
	EXPECT_TRUE( matchPathRegexp(testPathWithQuery,pathWithVariables) );

	string testNoMatchPath1 = "/hello/tomi";
	string testNoMatchPath2 = "/hello/tomi/bert/a";

	EXPECT_FALSE( matchPathRegexp(testNoMatchPath1,pathWithVariables) );
	EXPECT_FALSE( matchPathRegexp(testNoMatchPath2,pathWithVariables) );


}

TEST(UtilsTest, integratedUsingRouteParse) {
	string pathWithVariables = "/hello/:name/:surname";

	string testPath = "/hello/tomi/bert";

	map<string,string> result = routerParser(testPath,pathWithVariables);

	EXPECT_EQ(result.size(), 3);
	EXPECT_EQ(result["_route"],testPath);
	EXPECT_EQ(result["name"],"tomi");
	EXPECT_EQ(result["surname"],"bert");

	string testNotValidPath = "/hello/tomi/";

	map<string,string> resultNotValid = routerParser(testNotValidPath,pathWithVariables);

	EXPECT_EQ(resultNotValid.size(), 1);
	EXPECT_EQ(resultNotValid["_route"],testNotValidPath);

	string testPathWithQuery = "/hello/antonio/banderas?pelicula=elZorro";

	map<string,string> resultWithQuery = routerParser(testPathWithQuery,pathWithVariables);

	EXPECT_EQ(resultWithQuery.size(), 4);
	EXPECT_EQ(resultWithQuery["_route"],"/hello/antonio/banderas");
	EXPECT_EQ(resultWithQuery["name"],"antonio");
	EXPECT_EQ(resultWithQuery["surname"],"banderas");
	EXPECT_EQ(resultWithQuery["_query"],"pelicula=elZorro");



}

