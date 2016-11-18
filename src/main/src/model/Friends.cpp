#include <model/Friends.h>
#include <utils/DateUtils.h>

using namespace std;

#define FRIENDS_DB "Friends"

#define STATE_PENDING_FOR_ME 1
#define STATE_PENDING_FOR_HIM 2
#define STATE_ACCEPTED 3

DB* Friends::getDB(){
	return DBManager::getDB(FRIENDS_DB);
}

Json::Value Friends::getUserFriendsValue(string user_id){
	if (getDB()->exist(user_id)){
		Json::Value value = getDB()->getJSON(user_id);
		return value["friends"];
	}

	Json::Value new_friends;
	new_friends["friends"] = Json::objectValue;
	getDB()->storeJSON(user_id,new_friends);

	return new_friends["friends"];
}

bool Friends::storeUser(string user_id, Json::Value friend_data){

	Json::Value value = getDB()->getJSON(user_id);

	value["friends"] = friend_data;

	return getDB()->storeJSON(user_id,value);

}

Json::Value Friends::generateFriendData(int state){
	Json::Value data;
	data["state"] = state;
	data["timestamp"] = DateUtils::timestamp();

	return data;
}

ErrorMessage Friends::add(string source_user_id, string destination_user_id){
	ErrorMessage error;
	//source
	Json::Value source_friends = getUserFriendsValue(source_user_id);

	if (source_friends.isMember(destination_user_id)){
		error.addError("add friend","The friend is already on the list");
		return error;
	}

	source_friends[destination_user_id] = generateFriendData(STATE_PENDING_FOR_HIM);
	storeUser(source_user_id,source_friends);

	//destination
	Json::Value destination_friends = getUserFriendsValue(destination_user_id);

	if (destination_friends.isMember(source_user_id)){
		error.addError("add friend","The friend is already on the list");
		return error;
	}

	destination_friends[source_user_id] = generateFriendData(STATE_PENDING_FOR_ME);
	storeUser(destination_user_id,source_friends);

	return error;
}

ErrorMessage Friends::accept(string source_user_id, string destination_user_id){
	//source accept destination

	ErrorMessage error;
	Json::Value source_friends = getUserFriendsValue(source_user_id);

	if (!source_friends.isMember(destination_user_id)){
		error.addError("Accept friend","Friend is not on the list");
		return error;
	}

	source_friends[destination_user_id] = generateFriendData(STATE_ACCEPTED);
	storeUser(source_user_id,source_friends);


	Json::Value destination_friends = getUserFriendsValue(destination_user_id);
	if (!destination_friends.isMember(source_user_id)){
		error.addError("Accept friend","Friend is not on the list");
		return error;
	}

	destination_friends[source_user_id] = generateFriendData(STATE_ACCEPTED);
	storeUser(destination_user_id,source_friends);

	return error;
}

Json::Value Friends::listFriends(string user_id){
	Json::Value friends;
	Json::Value userDB = getDB()->getJSON(user_id);

	if(userDB.isMember("error")){
		friends[user_id] = Json::objectValue;
	}else {
		friends[user_id] = userDB["friends"];
	}

	return friends;
}

Json::Value Friends::listPendingFriends(string user_id){
	Json::Value all_friends = listFriends(user_id);
	all_friends = all_friends[user_id];

	Json::Value pending_list;
	pending_list[user_id] = Json::objectValue;
	Json::Value pending = pending_list[user_id];

	for( Json::ValueIterator itr = all_friends.begin() ; itr != all_friends.end() ; itr++ ) {
		Json::Value fr = all_friends[itr.index()];
		int state = fr["state"].asInt();
		if ( (state == STATE_PENDING_FOR_HIM) or (state == STATE_PENDING_FOR_ME)  ) {
			pending.append(fr);
		}
	}

	return pending_list;
}

ErrorMessage Friends::remove(string source_user_id, string destination_user_id){
	ErrorMessage error;
	Json::Value source_friends = getUserFriendsValue(source_user_id);

	if (!source_friends.isMember(destination_user_id)){
		error.addError("Remove friend","Friend is not on the list");
		return error;
	}

	source_friends.removeMember(destination_user_id);
	storeUser(source_user_id,source_friends);


	Json::Value destination_friends = getUserFriendsValue(destination_user_id);
	if (!destination_friends.isMember(source_user_id)){
		error.addError("Remove friend","Friend is not on the list");
		return error;
	}

	destination_friends.removeMember(source_user_id);
	storeUser(destination_user_id,source_friends);

	return error;
}
