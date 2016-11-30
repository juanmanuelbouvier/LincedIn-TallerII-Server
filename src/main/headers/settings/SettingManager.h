#ifndef SRC_MAIN_SRC_SETTINGS_SETTINGMANAGER_H_
#define SRC_MAIN_SRC_SETTINGS_SETTINGMANAGER_H_

#include <extern/json.h>
#include <string>

using namespace std;
/**
 * Setting Manager is a Singleton who contain all configurations of the settings file.
 */
class SettingManager {
private:
	static SettingManager* settingsInstance;

	Json::Value setting;

	SettingManager(){};

	bool areLoggerSettings();

public:
	static SettingManager* getInstance();
	static void deleteInstance();

	/**
	 * Read Json File who contain setting.
	 * @param file path.
	 * @return True if the file could be read.
	 */
	bool readFile(string file);

	/**
	 * Get a Json Structure of configuration File
	 * @return string message who contains an example of configuration file.
	 */
	string getJSONStructure();

	/**
	 * Get direct string Value of Json setting file.
	 * @param tag/member.
	 * @return value of tag/member.
	 */
	string getDirectValue( string tag );

	/**
	 * Getters of Logger settings
	 */
	int 	getLogLevel();
	string 	getLogFile();
	bool 	showLoggerInStdout();

	void 	initLogger();
	void 	initDefaultLogger();

	int 	getServerPort();

	string 	getDBFolder();

	string 	getSharedServerURL();


	/**
	 * Getters of Firebase settings
	 */
	string getFirebaseURL();
	string getFirebaseApiKey();

	virtual ~SettingManager(){};
};

#endif /* SRC_MAIN_SRC_SETTINGS_SETTINGMANAGER_H_ */
