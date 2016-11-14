#include <services/Access/AccessToken.h>
#include <exception>
#include <services/Logger/Logger.h>
#include <utils/JSONUtils.h>
#include <exception/AccessException.h>

#include <iostream>

const char* AccessToken::KEY = "LincedInAppServer=genkidama";
const jwt_alg_t AccessToken::ALGORITHM = JWT_ALG_HS256;
#define TOKEN_VALUE "token_data"

string jwt_get_body( jwt* JsonWebToken ){
	string dataDecoded = string(jwt_dump_str(JsonWebToken,0));
	return dataDecoded.substr(dataDecoded.find("}.") + 1);
}

Json::Value AccessToken::decode( string token ) {
	const unsigned char* key_c = (unsigned char*)KEY;

	jwt_t* JsonWebToken;

	int succes = jwt_decode(&JsonWebToken, token.c_str(),key_c, string(KEY).length());

	if (succes != 0){
		throw new AccessException( Log("AccessToken.cpp::" + to_string(__LINE__) + ".Cannot Decode Json Web Token Object",ERROR) );
	}

	//Separo porque viene siempre el header {"typ":"JWT","alg":"HS256"}.[NUESTRO JSON]
	string bodyToken = jwt_get_body(JsonWebToken);
	jwt_free(JsonWebToken);

	Json::Value dataJson;
	stringstream jsonDecodeString_s(bodyToken);
	jsonDecodeString_s >> dataJson;
	return dataJson;

	//TODO: When it fix, use it.
	//return JSONUtils::stringToJSON(jsonDecodeString);

}

string AccessToken::encode( Json::Value json ) {
	jwt_t* JsonWebToken;
	if ( jwt_new(&JsonWebToken) == 0 ) {
		if ( jwt_set_alg(JsonWebToken, ALGORITHM, (unsigned char*)KEY, string(KEY).length()) == 0) {
			Json::FastWriter writer;
			writer.omitEndingLineFeed();
			string plainJSON = writer.write(json);
			if ( jwt_add_grants_json(JsonWebToken,plainJSON.c_str()) == 0){
				string token = string( jwt_encode_str(JsonWebToken) );
				jwt_free(JsonWebToken);
				return token;
			}
		}

	}

	throw new AccessException( Log("AccessToken.cpp::" + to_string(__LINE__) + ".Cannot encode Json Value:\n\t" + json.toStyledString(),ERROR) );
}
