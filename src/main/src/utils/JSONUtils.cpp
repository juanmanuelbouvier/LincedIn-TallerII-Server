#include <utils/JSONUtils.h>
#include <iostream>


string JSONUtils::JSONToString( Json::Value json ) {
	Json::FastWriter writer;

	writer.omitEndingLineFeed();

	return writer.write(json);
}

Json::Value JSONUtils::stringToJSON(string json){
	Json::Value val;
	Json::Reader reader;
	bool parsedSuccess = reader.parse(json.c_str(),val);

	if (not parsedSuccess){
		val["error"] = "error on parse string";
	}

	return val;
}

Json::Value JSONUtils::findValue(Json::Value values, string key,string goal){
	for( Json::ValueIterator itr = values.begin() ; itr != values.end() ; itr++ ) {
		Json::Value val = values[itr.index()];
		if (goal.compare(val[key].asString())) {
			return val;
		}
	}

	Json::Value error;
	error["error"] = "not find key in values.";
	return error;

}

int JSONUtils::isValueInArray( Json::Value toFind, Json::Value array ) {
	if (!array.isArray()) {
		return -1;
	}
	int i = 0;
    for (const Json::Value& element : array) {
        if ( element == toFind ) {
        	return i;
        }
        i++;
    }
    return -1;
}


Json::Value JSONUtils::listToArrayValue(list<string> theList) {
	Json::Value array(Json::arrayValue);
	for ( const string& element : theList ) {
		array.append(element);
	}
	return array;
}


