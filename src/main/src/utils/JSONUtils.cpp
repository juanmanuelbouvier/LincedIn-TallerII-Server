#include <utils/JSONUtils.h>


string JSONUtils::JSONToString( Json::Value json ) {
	Json::FastWriter writer;

	writer.omitEndingLineFeed();

	return writer.write(json);
}
