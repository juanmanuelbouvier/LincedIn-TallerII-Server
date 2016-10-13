#include <services/Logger/Logger.h>

#include <iostream>
#include <fstream>
#include <utils/DateUtils.h>
#include "LincedInServerConfig.h"

using namespace std;

struct LoggerSetting LogSetting;

const string LoggerLevelToString[] = {"ERROR", "WARNING", "INFO", "DEBUG"};


void _LoggerInitLogMessage(){
	string version = to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR);
	Log("------------------------------------------------------------------",INFO);
	Log("\t\tNew Run of: LincedInAppServer | Version: " + version,INFO);
	Log("------------------------------------------------------------------",INFO);
}

/**
 * Init Logger<BR>
 *  level: Log level (0: "ERROR", 1: "WARNING", 2: "INFO", 3: "DEBUG").<BR>
 *  log_console: if true, the logger also use stdout.<BR>
 *  path: path to the file which logs.<BR>
 *
 */
void LoggerInit(int level, bool log_console, string path){
	LogSetting.LoggerLevel = level;
	LogSetting.LoggerConsole = log_console;
	LogSetting.LoggerPathFile = path;
	LogSetting.init = true;
    _LoggerInitLogMessage();
}

/*
 * Log a message in Logger.<BR>
 *  typeOfLog: ERROR, WARNING, INFO, DEBUG.
 *  Default typeOfLog is DEBUG.
 *
 */
void Log(string message, LogLevel typeOfLog){
    if (!LogSetting.init){
    	cout << "ERROR: Logger must be initialized with `LoggerInit(level,log_console,path)`" << endl;
    	return;
    }
	if (typeOfLog <= LogSetting.LoggerLevel) {
        std::fstream logfile;
        string full_msg = DateUtils::getTimeWithFormat() + "[" + LoggerLevelToString[typeOfLog] + "] " + message;
        logfile.open(LogSetting.LoggerPathFile.c_str(), std::fstream::app | std::fstream::out);
        logfile << full_msg << endl;

        if (LogSetting.LoggerConsole){
        	cout << full_msg << endl;
        }
    }
}

bool validLogLevel(int log_level){
	return (log_level <= DEBUG && log_level >= ERROR);
}
