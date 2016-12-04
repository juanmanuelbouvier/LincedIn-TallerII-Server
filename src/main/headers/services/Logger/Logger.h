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

/**
 * Init Logger<BR>
 *  level: Log level (0: "ERROR", 1: "WARNING", 2: "INFO", 3: "DEBUG").<BR>
 *  log_console: if true, the logger also use stdout.<BR>
 *  path: path to the file which logs.<BR>
 *
 */
void LoggerInit(int level, bool log_console, string path);

/*
 * Log a message in Logger.<BR>
 *  typeOfLog: ERROR, WARNING, INFO, DEBUG.
 *  Default typeOfLog is DEBUG.
 *  return string was logged.
 *
 */
string Log(string mensaje, LogLevel typeOfLog = DEBUG);

/**
 * Check if the log level is valid
 * @param integer log level
 * @return True if is valid
 */
bool validLogLevel(int log_level);

/**
 * Macro to Log with detailed file and line
 */
#define LOG(message,level) Log( StringUtils::generateFileMessage(__FILE__,__LINE__) + ".\n\t" + message,level);

#endif /* LOGGER_H_ */
