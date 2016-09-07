#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include "../../Utils/DateUtils.h"
#include "LincedInServerConfig.h"

using namespace std;

enum LogLevel {
    ERROR, WARNING, INFO, DEBUG
};

struct LoggerSetting{
	int LoggerLevel = ERROR;
	string LoggerPathFile = NULL;
	bool LoggerConsole = false;
	bool init = false;
};

void LoggerInit(int level, bool log_console, string path);
void Log(string mensaje, LogLevel typeOfLog = DEBUG);


#endif /* LOGGER_H_ */
