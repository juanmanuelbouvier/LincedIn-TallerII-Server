#include <utils/TokenUtils.h>
#include <model/User.h>
#include <services/Logger/Logger.h>
#include <services/Access/AccessToken.h>
#include <exception/TokenException.h>
#include <exception/AccessException.h>
#include <extern/json.h>
#include <utils/DateUtils.h>

using namespace std;

#define TOKEN_VALID_SECONDS 10*24*60 // 10 days

bool TokenUtils::isValidToken(string token){
	Json::Value decodeToken;

	try{
		decodeToken = AccessToken::decode(token);
	} catch (AccessException& e){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Token is invalid",INFO);
		return false;
	}

	string user_id = decodeToken["user_id"].asString();
	if (!User::exist(user_id)){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Token user_id not exist",WARNING);
		return false;
	}

	int now = DateUtils::timestamp();
	int token_timestamp = decodeToken["timestamp"].asInt();

	if (now - token_timestamp > TOKEN_VALID_SECONDS ){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Token defeated",WARNING);
		return false;
	}

	return true;
}

string TokenUtils::generateSessionToken(string user_id){

	//check User id
	if (!User::exist(user_id)){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Token user_id not exist",WARNING);
		throw TokenException("User id invalid: " + user_id);
	}

	Json::Value token;
	token["user_id"] = user_id;
	token["timestamp"] = DateUtils::timestamp();

	return AccessToken::encode(token);
}

User TokenUtils::userByToken(string token){

	if (!isValidToken(token)){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Invalid token on create user",ERROR);
		throw TokenException("Invalid Token");
	}

	Json::Value decodeToken =  AccessToken::decode(token);

	return User(decodeToken["user_id"].asString());
}

string TokenUtils::userIDByToken(string token){
	if (!isValidToken(token)){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Invalid token on create user",ERROR);
		throw TokenException("Invalid Token");
	}

	Json::Value decodeToken =  AccessToken::decode(token);

	return decodeToken["user_id"].asString();
}


string TokenUtils::renovateToken(string token){

	try{
		Json::Value	decodeToken = AccessToken::decode(token);
		decodeToken["timestamp"] = DateUtils::timestamp();
		return AccessToken::encode(decodeToken);
	} catch (AccessException& e){
		Log("TokenUtils.cpp::" + to_string(__LINE__) + ".Cannot decode Token",ERROR);
		throw TokenException("Cannot decode token");
	}
	return "";
}
