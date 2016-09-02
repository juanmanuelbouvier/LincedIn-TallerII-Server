#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include "../Utils/DateUtils.h"
#include "LincedInServerConfig.h"

using namespace std;

#define DEFAULT_LOG_PATH "config/logs/ServerLog.log" 

enum LogLevel {
    ERROR, WARNING, INFO, DEBUG
};

struct LoggerSetting{
	int LoggerLevel = ERROR;
	string LoggerPathFile = DEFAULT_LOG_PATH;
	bool LoggerConsole = false;
};

void LoggerInit(int level = ERROR, bool log_console = false, string path = NULL);
void Log(string mensaje, LogLevel typeOfLog = DEBUG);


#endif /* LOGGER_H_ */
