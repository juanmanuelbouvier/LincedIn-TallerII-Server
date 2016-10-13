#include <settings/SettingManager.h>
#include <services/Logger/Logger.h>
#include <utils/PathUtils.h>

#include <fstream>
#include <iostream>

using namespace std;

#define DEFAULT_SERVER_PORT		8081
#define DEFAULT_LOG_LEVEL		DEBUG
#define DEFAULT_LOG_STDOUT		true
#define DEFAULT_LOG_FILE		"logs/LincedInAppServer.log"
#define DEFAULT_SHARED_URL 		"lincedin.herokuapp.com:80"

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
			cout << "Error at reading settings file (\"" << file <<"\"). Check if exists" << endl;
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
				"\t}\n"
				"\tport: type int\tSets port for incomming connections. Default: " + to_string(DEFAULT_SERVER_PORT) + "\n"
				"\tshared_server_url: type string\t Url to shared server client. Format \"(URL|IP):PORT\". Default: \"" + string(DEFAULT_SHARED_URL) + "\"\n"
			"}\n\n";
	return message;
}

string SettingManager::getDirectValue( string tag ) {
	if (setting[tag].isConvertibleTo(Json::stringValue)) {
		return setting[tag].asString();
	}
	return "";
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
				cout << "Invalid Log Level (" << log_level << "). Using default [" << DEFAULT_LOG_LEVEL << "]" << endl;
				return DEFAULT_LOG_LEVEL;
			}
		} else {
			cout << "Invalid level logger setting value. Using default" << endl;
		}
	}
	return DEFAULT_LOG_LEVEL;
}

string SettingManager::getLogFile() {
	if (areLoggerSettings()) {
		Json::Value filePath = setting["logger"]["file"];
		if (filePath.isConvertibleTo(Json::stringValue)) {
			string file = filePath.asString();
			string pathOfLog = PathUtils::getFolderOfFilePath(file) + "/";
			if ( PathUtils::isValidPath(pathOfLog) ){
				return file;
			} else {
				cout << "Invalid Log Path (folder '" + file + "' not exist). Using Default [" + DEFAULT_LOG_FILE + "]" << endl;
				return DEFAULT_LOG_FILE;
			}
		} else {
			cout << "Invalid file logger setting. Using default";
		}
	}
	return DEFAULT_LOG_FILE;
}

bool SettingManager::showLoggerInStdout(){
	if (areLoggerSettings()){
		Json::Value booleanStdout = setting["logger"]["show_in_stout"];
		if (booleanStdout.isConvertibleTo(Json::booleanValue)){
			return booleanStdout.asBool();
		} else {
			cout << "Cannot read show_in_stdout value. Work with default." << endl;
		}
	}
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
	int level;
	string file;
	bool stdout;
	try {
		if ( !areLoggerSettings() ){
			cout << "No setting for log detected. Using default values:" << endl;
			cout << "\tlevel:\t\t" << DEFAULT_LOG_LEVEL << endl;
			cout << "\tfile:\t\t" << DEFAULT_LOG_FILE << endl;
			cout << "\tin stdout:\t" << (DEFAULT_LOG_STDOUT ? "true" : "false") << endl << endl;
		}
		level 	= getLogLevel();
		file 	= getLogFile();
		stdout	= showLoggerInStdout();
	} catch (Json::RuntimeError& e) {
		cout << "Error while reading setting of logger. Init with default values" << endl;
		initDefaultLogger();
	}
	LoggerInit(level,stdout,file);
}

void SettingManager::initDefaultLogger(){
	LoggerInit(DEFAULT_LOG_LEVEL,DEFAULT_LOG_STDOUT,DEFAULT_LOG_FILE);
}


