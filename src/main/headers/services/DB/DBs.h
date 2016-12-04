#ifndef SRC_MAIN_HEADERS_SERVICES_DB_DBS_H_
#define SRC_MAIN_HEADERS_SERVICES_DB_DBS_H_

#include <string>
#include <list>

using namespace std;


namespace Databases {

const string DB_USER 					= "User";
const string DB_EMAIL 					= "Email";
const string DB_CHAT 					= "Chat";
const string DB_CHATS 					= "Chats";
const string DB_FRIENDS 				= "Friends";
const string DB_GEO 					= "Geolocalization";
const string DB_USER_GEO 				= "User_Geolocalization";
const string DB_IMAGE					= "Image";
const string DB_RECOMMENDATION			= "Recommendations";
const string DB_RECOMMENDATION_COUNT 	= "CountRecommendations";
const string DB_USER_ACTIVITY			= "UserActivity";
const string DB_SHARED_SERVER_CACHE		= "SharedCache";

const list<string> ALL = {
		DB_USER,
		DB_EMAIL,
		DB_CHAT,
		DB_CHATS,
		DB_FRIENDS,
		DB_GEO,
		DB_USER_GEO,
		DB_IMAGE,
		DB_RECOMMENDATION,
		DB_RECOMMENDATION_COUNT,
		DB_USER_ACTIVITY,
		DB_SHARED_SERVER_CACHE
};

};

#endif /* SRC_MAIN_HEADERS_SERVICES_DB_DBS_H_ */
