#include <model/Image.h>
#include <services/Logger/Logger.h>

using namespace std;

#define IMAGE_DB "Image"
#define BASE_URL "/img/"
#define METADATA_KEY "metadata"
#define BASE_ID "lincedin"

DB* Image::getDB(){
	return DBManager::getDB(IMAGE_DB);
}

string Image::urlByBase64(string base64Image){

	string id = getNextID();

	return (getDB()->store(id,base64Image) && amountMetadata(id)) ? BASE_URL + id : "";

}

string Image::getBase64(string id){
	return getDB()->get(id);
}

bool Image::remove(string url){

	//quito la base del url
	string base_url = BASE_URL;
	string key = url.erase(0,base_url.size());

	return getDB()->Delete(key);
}

string Image::getNextID(){
	DB* DB = getDB();
	if (!DB->exist(METADATA_KEY)){
		Json::Value init_metadata;
		init_metadata["last_id"] = BASE_ID + to_string(0);
		init_metadata["count"] = 0;

		DB->storeJSON(METADATA_KEY,init_metadata);
	}

	Json::Value metadata = DB->getJSON(METADATA_KEY);
	string base_id = BASE_ID;
	string last_id = metadata["last_id"].asString();
	int number_last_id = atoi(last_id.erase(0,base_id.size()).c_str());
	number_last_id++;


	return BASE_ID + to_string(number_last_id);
}

bool Image::amountMetadata(string last_id){
	if (getDB()->exist(METADATA_KEY)){
		Json::Value metadata = getDB()->getJSON(METADATA_KEY);
		metadata["last_id"] = last_id;
		metadata["count"] = metadata["count"].asInt() + 1;

		return getDB()->storeJSON(METADATA_KEY,metadata);
	}

	return false;
}

bool Image::exist(string id){
	return getDB()->exist(id);
}
