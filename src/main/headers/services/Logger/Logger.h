#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <utils/StringUtils.h>

using namespace std;

enum LogLevel {
    ERROR, WARNING, INFO, DEBUG
};

struct LoggerSetting{
	int LoggerLevel = ERROR;
	string LoggerPathFile = "";
	bool LoggerConsole = false;
	bool init = false;
};

void LoggerInit(int level, bool log_console, string path);
string Log(string mensaje, LogLevel typeOfLog = DEBUG);
string generateFileMessage( string file, int line );
bool validLogLevel(int log_level);

#define LOG(message,level) Log( StringUtils::generateFileMessage(__FILE__,__LINE__) + ".\n\t" + message,level);

#endif /* LOGGER_H_ */
