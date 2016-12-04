#include <settings/SettingManager.h>
#include <services/Logger/Logger.h>
#include <utils/PathUtils.h>

#include <fstream>
#include <iostream>
#include <sys/stat.h>

using namespace std;

#define DEFAULT_SERVER_PORT		8081
#define DEFAULT_LOG_LEVEL		DEBUG
#define DEFAULT_LOG_STDOUT		true
#define DEFAULT_LOG_FILE		"LincedInAppServer.log"
#define DEFAULT_SHARED_URL 		"lincedin.herokuapp.com:80"
#define DEFAULT_DB_FOLDER		"db"
#define DEFAULT_FIREBASE_URL	"fcm.googleapis.com"
#define DEFAULT_FIREBASE_API_KEY "AIzaSyBE9xn7X8eo86rxJ_ggiQt6IPx-Oxsb1Kg"
#define DEFAULT_ELASTIC_HOST	"localhost:9200"


SettingManager* SettingManager::settingsInstance = NULL;

SettingManager* SettingManager::getInstance(){
	if (!settingsInstance) {
		settingsInstance = new SettingManager();
	}
	return settingsInstance;
}

void SettingManager::deleteInstance(){
	delete settingsInstance;
	settingsInstance = NULL;
}

bool SettingManager::readFile( string file ) {
	try {
		ifstream stream_file(file, ifstream::binary);
		if (!stream_file.good()){
			Log("Error at reading settings file (\""+ file +"\"). Check if exists",WARNING);
			return false;
		}
		stream_file >> setting;
	} catch (Json::RuntimeError& e) {
		return false;
	}
	return true;
}

string SettingManager::getJSONStructure(){
	string message = ""
			"Setting JSON structure:\n"
			"{\n"
				"\tlogger: {\n"
					"\t\tlevel: type number \t\tSets log level. ERROR(0), WARNING(1), INFO(2), DEBUG(3). Default: " + to_string(DEFAULT_LOG_LEVEL) + "\n"
					"\t\tfile: type string\t\tSet Path to write log. Default: \"" + string(DEFAULT_LOG_FILE) + "\"\n"
					"\t\tshow_in_stdout: type boolean\tIf true the logs also be displayed in stdout. Default: " + (DEFAULT_LOG_STDOUT ? "true" : "false") + "\n"
				"\t},\n"
				"\tport: type int\tSets port for incomming connections. Default: " + to_string(DEFAULT_SERVER_PORT) + ",\n"
				"\tshared_server_url: type string\t Url to shared server client. Format \"(URL|IP):PORT\". Default: \"" + string(DEFAULT_SHARED_URL) + "\",\n"
				"\tfirebase_url: type string\t Url to firebase server client. Format \"(URL)\". Default: \"" + string(DEFAULT_FIREBASE_URL) + "\",\n"
				"\tfirebase_api_key: type string\t Api key to firebase server. Default: \"" + string(DEFAULT_FIREBASE_API_KEY) + "\",\n"
				"\tdb_folder: type string\t Folder who store DB files. Default: \"" + string(DEFAULT_DB_FOLDER) + "\",\n"
				"\telastic_host: type string\t Elastic Search Client host. Default: \"" + string(DEFAULT_ELASTIC_HOST) + "\"\n"
			"}\n\n";
	return message;
}

string SettingManager::getDirectValue( string tag ) {
	if (setting[tag].isConvertibleTo(Json::stringValue)) {
		return setting[tag].asString();
	}
	return "";
}

string SettingManager::getDBFolder() {
	string dbFolder = getDirectValue("db_folder");
	if ( dbFolder.length() > 0) {
		if (PathUtils::isValidPath(dbFolder)) {
			return dbFolder;
		}
	}
	Log("Invalid DB folder. Check if exist. Using default.",WARNING);
	mkdir(DEFAULT_DB_FOLDER, ACCESSPERMS);
	return DEFAULT_DB_FOLDER;
}

bool SettingManager::areLoggerSettings(){
	return setting.isMember("logger");
}

int SettingManager::getLogLevel(){
	if (areLoggerSettings()) {
		Json::Value log_level_value = setting["logger"]["level"];
		if (log_level_value.isConvertibleTo(Json::intValue)) {
			int log_level = log_level_value.asInt();
			if (validLogLevel(log_level)){
				return log_level;
			} else {
				Log("Invalid Log Level ("+ log_level_value.asString() + "). Using default [" + to_string(DEFAULT_LOG_LEVEL) + "]",WARNING);
				return DEFAULT_LOG_LEVEL;
			}
		}
	}

	cout <<"[WARNING] Not found or invalid level logger setting value. Using default: " << DEFAULT_LOG_LEVEL;
	return DEFAULT_LOG_LEVEL;
}

string SettingManager::getLogFile() {
	if (areLoggerSettings()) {
		Json::Value filePath = setting["logger"]["file"];
		if (filePath.isConvertibleTo(Json::stringValue)) {
			string file = filePath.asString();
			string pathOfLog = PathUtils::getFolderOfFilePath(file) + "/";
			if ( PathUtils::isValidPath(pathOfLog) or pathOfLog.size() == 1 ){
				return file;
			}
		}
	}
	cout << "[WARNING] Invalid or not Found file logger setting. Using default: " << DEFAULT_LOG_FILE << endl;
	return DEFAULT_LOG_FILE;
}

bool SettingManager::showLoggerInStdout(){
	if (areLoggerSettings()){
		Json::Value booleanStdout = setting["logger"]["show_in_stout"];
		if (booleanStdout.isConvertibleTo(Json::booleanValue)){
			return booleanStdout.asBool();
		}
	}
	cout << "[WARNING] Cannot read show_in_stdout value. Work with default." << (DEFAULT_LOG_STDOUT ? "true" : "false") << endl;
	return DEFAULT_LOG_STDOUT;
}

int SettingManager::getServerPort(){
	string port = getDirectValue("port");
	if (port != ""){
		int int_port = atoi( port.c_str() );
		if (int_port >= 0) {
			return int_port;
		}
	}
	Log("No port configuration is detected. Using default: " + to_string(DEFAULT_SERVER_PORT),WARNING);
	return DEFAULT_SERVER_PORT;
}

string SettingManager::getSharedServerURL(){
	string url = getDirectValue("shared_server_url");
	if (url != ""){
		return url;
	}
	Log("No URL for Shared Server API was detected. Using default: \"" + string(DEFAULT_SHARED_URL) + "\"",WARNING);
	return DEFAULT_SHARED_URL;
}

void SettingManager::initLogger(){
	int level 	= getLogLevel();
	string file = getLogFile();
	bool stdout	= showLoggerInStdout();
	LoggerInit(level,stdout,file);
}

void SettingManager::initDefaultLogger(){
	LoggerInit(DEFAULT_LOG_LEVEL,DEFAULT_LOG_STDOUT,DEFAULT_LOG_FILE);
}


string SettingManager::getFirebaseURL(){
	string url = getDirectValue("firebase_url");
	if (url != ""){
		return url;
	}
	Log("No URL for Firebase API was detected. Using default: \"" + string(DEFAULT_FIREBASE_URL) + "\"",WARNING);
	return DEFAULT_FIREBASE_URL;
}

string SettingManager::getFirebaseApiKey(){
	string key = getDirectValue("firebase_api_key");
	if (key != ""){
		return key;
	}
	Log("No api key for Firebase API was detected. Using default: \"" + string(DEFAULT_FIREBASE_API_KEY) + "\"",WARNING);
	return DEFAULT_FIREBASE_API_KEY;
}

string SettingManager::getElasticHost(){
	string key = getDirectValue("elastic_host");
	if (key != ""){
		return key;
	}
	Log("No host for elastic client was detected. Using default: \"" + string(DEFAULT_ELASTIC_HOST) + "\"",WARNING);
	return DEFAULT_ELASTIC_HOST;
}

