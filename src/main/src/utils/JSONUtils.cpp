#include <utils/JSONUtils.h>


string JSONUtils::JSONToString( Json::Value json ) {
	Json::FastWriter writer;

	writer.omitEndingLineFeed();

	return writer.write(json);
}

Json::Value JSONUtils::stringToJSON(string json){
	Json::Value val;
	Json::Reader reader;
	bool parsedSuccess = reader.parse(json,val,false);

	if (not parsedSuccess){
		val["error"] = "error on parse string";
	}

	return val;
}
