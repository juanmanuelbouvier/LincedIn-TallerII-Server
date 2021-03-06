#include <services/Handlers/SearchHandler.h>
#include <extern/json.h>
#include <services/Search/ElasticClient.h>
#include <utils/JSONUtils.h>
#include <model/Geolocalization.h>
#include <model/Recommendation.h>
#include <services/Logger/Logger.h>
#include <services/HTTP/HTTPResponseConstants.h>

Json::Value joinResult(Json::Value dataSearch) {
	/* Expected:
	 *  {
	 *  	"r1":{
	 *  		"a" : ..
	 *  		"b" : ..
	 *  		"c" : ..
	 *  	},
	 * 		"r2":{
	 * 			"a" : ..
	 * 			"c" : ..
	 * 		}
	 *  }
	 * Result: {
	 * 		"users_found" : ["a","c"]
	 * }
	 */
	Json::Value::Members members = dataSearch.getMemberNames();
	string firstMember = members[ members.size() - 1 ];
	members.pop_back();
	Json::Value firstResult = dataSearch[firstMember];
	Json::Value users_found(Json::arrayValue);

	for ( auto m : firstResult.getMemberNames() ) {
		Json::Value candidate;
		candidate[m] = firstResult[m];
		bool join = true;
		for ( auto m2 : members ) {
			if ( !dataSearch[m2].isMember(m) ) {
				join = false;
				continue;
			}
			candidate[m] = dataSearch[m2][m];
		}
		if (join) {
			users_found.append(m);
		}
	}
	Json::Value joined;
	joined["users_found"] = users_found;
	return joined;
}

HTTPResponse* SearchHandler::handle(HTTPRequest* request) {
	Json::Value query = JSONUtils::queryToJson(request->getQuery());

	//1. Search Query
	Json::Value queryData;
	if (query.isMember("text") && query["text"].isString()) {
		LOG("Filter by Query Text: \"" + query["text"].asString() + "\"", DEBUG);
		queryData["query"]["query_string"]["query"] = query["text"].asString();
	}

	//2. Filter Skills
	if ( query.isMember("skill") ) {
		LOG("Filter by skills: " + query["skill"].toStyledString(), DEBUG);
		if (query["skill"].isArray()) {
			int size = query["skill"].size();
			Json::Value arraySkills(Json::arrayValue);			
			for (int i = 0; i < size; i++) {
				arraySkills.append(query["skill"][i].asString());
			}
			queryData["query"]["term"]["skills.name"] = arraySkills;
		} else if (query["skill"].isString()) {
			queryData["query"]["term"]["skills.name"] = query["skill"].asString();
		}
	}

	Json::Value toJoin;
	if ( queryData.isMember("query") > 0 ) {
		ElasticClient el;
		LOG("Elastic Query\n" + queryData.toStyledString(),DEBUG);
		if (el.isAlive()) {
			toJoin["text"] = el.search("lincedin","user",queryData, true);
		}
	}

	// 3. Search with geolocation
	if ( query.isMember("latitude") && query.isMember("longitude")) {
		Json::Value geoData;
		geoData["latitude"] = query["latitude"];
		geoData["longitude"] = query["longutude"];
		if ( query.isMember("range") && !query["range"].isArray() ) {
			geoData["range"] = query["range"].asString();
		}
		LOG("Filter with Geodata: \n" + geoData.toStyledString(),DEBUG);
		toJoin["geo"] = Geolocalization::findUsersByLocation(geoData);
	}


	// 4. Filter Top User
	if ( query.isMember("top") && query["top"].isString()) {
		LOG("Filter top: " + query["top"].asString() + " (defined with recommendations)",DEBUG);
		Json::Value tops = Recommendation::getUsersMostRecommendation( stoi( query["top"].asString() ) );
		Json::Value user_id_top;
		for (int i=0; i < tops.size();i++) {
			user_id_top[tops[i]["user_id"].asString()] = tops[i]["count_recommendations"];
		}
		toJoin["top"] = user_id_top;
	}

	Json::Value result;
	result = (toJoin.size() == 0) ? result : joinResult(toJoin);
	return ResponseBuilder::createJsonResponse(CODE_OK,result);

}

