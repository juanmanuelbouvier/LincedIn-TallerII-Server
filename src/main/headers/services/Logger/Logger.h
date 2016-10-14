#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>


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
bool validLogLevel(int log_level);

#endif /* LOGGER_H_ */
