#include <UtilsTest.h>

#include <utils/PathUtils.h>
#include <utils/StringUtils.h>
#include <utils/VectorUtils.h>
#include <utils/DateUtils.h>
#include <utils/JSONUtils.h>
#include <utils/ErrorMessage.h>
#include <utils/GeoUtils.h>

#include <ctime>
#include <extern/json.h>

#include <string>
#include <list>

using namespace std;

TEST(UtilsTest, getFolderOfFilePath) {
	string path = "hello/world/file.txt";
	string result = PathUtils::getFolderOfFilePath(path);
	EXPECT_EQ("hello/world", result);

	string path2 = "file.txt";
	EXPECT_EQ(PathUtils::getFolderOfFilePath(path2), "");
}

TEST(UtilsTest, fakePathIsInvalid) {
	bool fakePath = PathUtils::isValidPath("fakepathintherepository/");
	EXPECT_FALSE(fakePath);
}

TEST(UtilsTest, createdPathIsValid) {
	//This work if the test are run with make in basedir project
	bool truePath = PathUtils::isValidPath(".temp-test/");
	EXPECT_TRUE(truePath);

	bool truePathNotEnd = PathUtils::isValidPath(".temp-test");
	EXPECT_TRUE(truePathNotEnd);
}

TEST(UtilsTest, splitPath) {
	string path = "hello/world/hi";
	vector<string> theSplitPath = StringUtils::splitString(path,"/");

	vector<string> expectedSplit = {"hello","world","hi"};

	EXPECT_EQ(theSplitPath, expectedSplit);
}

TEST(UtilsTest, stringReplace) {
	string s = "hello world";
	string r1 = StringUtils::replace(s," ","");
	EXPECT_EQ(r1, "helloworld");

	string r2 = StringUtils::replace(s,"o","a");
	EXPECT_EQ(r2, "hella warld");

	string r3 = StringUtils::replace(s,"hello world","goodbye");
	EXPECT_EQ(r3, "goodbye");

	string r4 = StringUtils::replace(s,"","goodbye");
	EXPECT_EQ(r4,s);

	string r5 = StringUtils::replace("nospace"," ","");
	EXPECT_EQ(r5,"nospace");
}

TEST(UtilsTest, upperCaseAndLoweCase) {
	string s = "theStrigWith UPPErAndLowWer";
	string r1 = StringUtils::toLowerCase(s);
	EXPECT_EQ(r1,"thestrigwith upperandlowwer");

	string r2 = StringUtils::toUpperCase(s);
	EXPECT_EQ(r2,"THESTRIGWITH UPPERANDLOWWER");
}

TEST(UtilsTest, randomPassword) {
	string pass = StringUtils::generateRandomPassword();

	EXPECT_TRUE(pass.size() > 0);
}

TEST(UtilsTest, encodeURL) {
	string urlToDecode = "the+%23hello%20world%21";
	string expected = "the #hello world!";

	EXPECT_EQ(StringUtils::unescapeString(urlToDecode), expected);
}

TEST(UtilsTest, decodeURL) {
	string urlToEncode = "#hello world!";
	string expected  = "%23hello%20world%21";

	EXPECT_EQ(StringUtils::urlEncode(urlToEncode), expected);
}

TEST(UtilsTest, ecryptPassword) {
	string password = "123";
	string passEncrypted = StringUtils::passwordEncrypt(password);

	string passDecrypted = StringUtils::passwordDecrypt(passEncrypted);

	//EXPECT_NE(password, passEncrypted);
	EXPECT_EQ(password, passDecrypted);
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

	string testPathWithQuery = "/hello/antonio/banderas?film=elZorro";

	map<string,string> resultWithQuery = PathUtils::routerParser(testPathWithQuery,pathWithVariables);

	EXPECT_EQ(resultWithQuery.size(), 4);
	EXPECT_EQ(resultWithQuery["_route"],"/hello/antonio/banderas");
	EXPECT_EQ(resultWithQuery["name"],"antonio");
	EXPECT_EQ(resultWithQuery["surname"],"banderas");
	EXPECT_EQ(resultWithQuery["_query"],"film=elZorro");

}

TEST(UtilsTest, ErrorMessageNotEmpty) {
	ErrorMessage error;
	string errorkey1 = "key1";
	string error1 = "error 1";
	error.addError(errorkey1,error1);

	string errorkey2 = "key2";
	string error2 = "error 2";
	error.addError(errorkey2,error2);

	string errorkey3 = "key3";
	string error3 = "error 3";
	error.addError(errorkey3,error3);

	EXPECT_FALSE(error.empty());
	EXPECT_FALSE(error.summary().empty());

}

TEST(UtilsTest, ErrorMessageGetError) {
	ErrorMessage error;
	string errorkey1 = "key1";
	string error1 = "error 1";
	error.addError(errorkey1,error1);

	string errorkey2 = "key2";
	string error2 = "error 2";
	error.addError(errorkey2,error2);

	string errorkey3 = "key3";
	string error3 = "error 3";
	error.addError(errorkey3,error3);

	EXPECT_EQ(error.getError(errorkey2),error2);

}


TEST(UtilsTest, DuummyGetTime) {
	string date = DateUtils::getTimeWithFormat("Rand0m[%Y]Rand0m");

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	string expectedYear = to_string(1900 + timePtr->tm_year);

	EXPECT_EQ(date,"Rand0m[" + expectedYear + "]Rand0m");

}

TEST(UtilsTest, DateConvert) {
	string date = "12/04/1994";

	string e1 = "1994-04-12 00:00:00";
	string r1 = DateUtils::parseDate(date,"%d/%m/%Y");
	EXPECT_EQ(e1,r1);

	string e2 = "00hs 00m 00s 1994 hello 12 -======-----=- 04]";
	string r2 = DateUtils::parseDate(date,"%d/%m/%Y","%Hhs %Mm %Ss %Y hello %d -======-----=- %m]");
	EXPECT_EQ(e2,r2);

}

TEST(UtilsTest, timestamp) {
	string timestamp_string = DateUtils::getTimeWithFormat("%s");
	int timestamp = DateUtils::timestamp();

	EXPECT_GE(timestamp,atoi(timestamp_string.c_str()));

}


TEST(UtilsTest, JSONfindValueInValues) {
	Json::Value values = Json::Value(Json::arrayValue);

	Json::Value val;
	val["name"] = "Pep";
	val["position"] = "MC";
	values.append(val);

	Json::Value val2;
	val2["name"] = "Mou";
	val2["position"] = "DC";
	values.append(val2);

	Json::Value val3;
	val3["name"] = "FME";
	val3["position"] = "LI";
	values.append(val3);

	Json::Value res = JSONUtils::findValue(values,"name","Pep");

	EXPECT_EQ(val,res);

	Json::Value res2 = JSONUtils::findValue(values,"name","FAS");

	EXPECT_TRUE(res2.isMember("error"));
}


TEST(UtilsTest, stringToJSON) {
	Json::Value val;
	val["name"] = "Pep";
	val["position"] = "MC";
	val["other"] = "rugbier";

	Json::Value res = JSONUtils::stringToJSON(val.toStyledString());

	EXPECT_EQ(val,res);

	Json::Value fail = JSONUtils::stringToJSON("Invalid Json Value");
	EXPECT_TRUE(fail["error"].isString());

	Json::Value emptyFail = JSONUtils::stringToJSON("");
	EXPECT_TRUE(emptyFail["error"].isString());
}

TEST(UtilsTest, listToJsonArray) {
	list<string> aList = {"h","e","l","l"};
	Json::Value array = JSONUtils::listToArrayValue(aList);
	EXPECT_EQ(array.size(),4);
	EXPECT_EQ(array[0],"h");
	EXPECT_EQ(array[1],"e");
	EXPECT_EQ(array[2],"l");
	EXPECT_EQ(array[3],"l");
}


TEST(UtilsTest, JSONToString) {
	Json::Value val(Json::arrayValue);
	val.append(1);
	val.append(2);
	val.append(3);

	Json::Value res = JSONUtils::JSONToString(val);
	string expected = "[1,2,3]";
	EXPECT_EQ(res,expected);

}

TEST(UtilsTest, JSONValueInArray) {
	Json::Value array(Json::arrayValue);
	array.append(1);
	array.append(2);
	array.append(3);
	array.append(4);
	array.append(5);

	int res = JSONUtils::isValueInArray(4,array);
	EXPECT_EQ(res,3);

	int fail = JSONUtils::isValueInArray(0,array);
	EXPECT_EQ(fail,-1);

	Json::Value object;
	int fail_array = JSONUtils::isValueInArray("tomi",object);
	EXPECT_EQ(fail_array,-1);
}



TEST(UtilsTest, GeoUtilsDistance) {
	Location location1 = {45.7597, 4.8422}; //Paris
	Location location2 = {48.8567, 2.3508}; //Lyon
	double distance = GeoUtils::distance(location1,location2);
	double expected = 392.21671780659625;
	EXPECT_DOUBLE_EQ(distance,expected);
}

TEST(UtilsTest, GeoUtilsValidLocation) {
	Location location_valid = {45.7597, 4.8422};
	Location location_invalid = {-98.8567, 2.3508};
	Location location_invalid2 = {-38.8567, -200.3508};
	EXPECT_TRUE(GeoUtils::isValid(location_valid));
	EXPECT_FALSE(GeoUtils::isValid(location_invalid));
	EXPECT_FALSE(GeoUtils::isValid(location_invalid2));

}

TEST(UtilsTest, GeoUtils) {
	double n1 = 4.4928;
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,3),4.493);
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,4),n1);
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,5),n1);
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,2),4.49);
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,1),4.5);
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,0),4);
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n1,-1),n1);

	double n2 = 4.5928;
	ASSERT_DOUBLE_EQ(GeoUtils::roundNumber(n2,0),5);
}

bool LocationInArray(Location to_find, list<Location> locations, int presicion) {
	double lat = GeoUtils::roundNumber(to_find.latitude, presicion);
	double lon = GeoUtils::roundNumber(to_find.longitude,presicion);
	for (Location& l : locations) {
		if (l.latitude == lat && l.longitude == lon) {
			return true;
		}
	}
	return false;
}

TEST(UtilsTest, GeoUtilNeighbour) {
	Location loc = {-25.2967829,-57.5946782};
	list<Location> neighbours = GeoUtils::getNeighbours(loc,0.11,3);

	Location l1 = {	-25.298,-57.596 };
	Location l2 = { -25.298,-57.595 };
	Location l3 = { -25.298,-57.594 };
	Location l4 = { -25.297,-57.596 };
	Location l5 = { -25.297,-57.594 };
	Location l6 = { -25.296,-57.596 };
	Location l7 = { -25.296,-57.595 };
	Location l8 = { -25.296,-57.594 };
	list<Location> expected = {l1,l2,l3,l4,l5,l6,l7,l8};

	for (Location& l : neighbours) {
		ASSERT_TRUE( LocationInArray(l,expected, 3) );
	}

}


