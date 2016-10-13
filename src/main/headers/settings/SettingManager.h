#ifndef SRC_MAIN_SRC_SETTINGS_SETTINGMANAGER_H_
#define SRC_MAIN_SRC_SETTINGS_SETTINGMANAGER_H_

#include <extern/json.h>
#include <string>

using namespace std;

class SettingManager {
private:
	static SettingManager* settingsInstance;

	Json::Value setting;

	SettingManager();

	bool areLoggerSettings();

public:
	static SettingManager* getInstance();

	bool readFile(string file);

	string getDirectValue( string tag );

	int getLogLevel();
	string getLogFile();
	bool showLoggerInStdout();

	int getServerPort();

	void initLogger();
	void initDefaultLogger();

	virtual ~SettingManager();
};

#endif /* SRC_MAIN_SRC_SETTINGS_SETTINGMANAGER_H_ */
