#include <utils/JSONUtils.h>
#include <iostream>
#include <utils/StringUtils.h>


string JSONUtils::JSONToString( Json::Value json ) {
	Json::FastWriter writer;

	writer.omitEndingLineFeed();

	return writer.write(json);
}

Json::Value JSONUtils::stringToJSON(string json){
	Json::Value val;
	Json::Reader reader;
	if ( !json.empty() ) {
		bool parsedSuccess = reader.parse(json.c_str(),val);
		if (not parsedSuccess){
			val["error"] = "Reader. error on parse string";
		}
	} else {
		val["error"] = "Empty String. error on parse string";
	}
	return val;
}

Json::Value JSONUtils::findValue(Json::Value values, string key,string goal){
	for( Json::ValueIterator itr = values.begin() ; itr != values.end() ; itr++ ) {
		Json::Value val = values[itr.index()];
		if (goal == val[key].asString()) {
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

Json::Value JSONUtils::queryToJson( string query ) {
	Json::Value queryData;
	vector<string> parameters = StringUtils::splitString(query,"&");
	for (string& p : parameters) {
		vector<string> arg_value = StringUtils::splitString(p,"=");
		if (arg_value.size() < 2 ) {
			continue;
		}
		string arg = arg_value[0];
		string val = arg_value[1];
		if ( queryData.isMember(arg) ) {
			if (queryData[arg].isArray()) {
				queryData[arg].append(val);
			} else {
				Json::Value array(Json::arrayValue);
				array.append(queryData[arg]);
				array.append(val);
				queryData[arg] = array;
			}
		} else {
			queryData[arg] = val;
		}
	}
	return queryData;
}


