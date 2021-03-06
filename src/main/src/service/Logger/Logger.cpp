#include <services/Logger/Logger.h>

#include <iostream>
#include <fstream>
#include <utils/DateUtils.h>
#include "LincedInServerConfig.h"

using namespace std;

struct LoggerSetting LogSetting;

const string LoggerLevelToString[] = {"ERROR", "WARNING", "INFO", "DEBUG"};


void LoggerInit(int level, bool log_console, string path){
	LogSetting.LoggerLevel = level;
	LogSetting.LoggerConsole = log_console;
	LogSetting.LoggerPathFile = path;
	LogSetting.init = true;
}



string Log(string message, LogLevel typeOfLog){
    string full_msg = "";
	if (!LogSetting.init){
		full_msg = "ERROR: Logger must be initialized with `LoggerInit(level,log_console,path)`";
    	cout << full_msg << endl;
    	return full_msg;
    }
	if (typeOfLog <= LogSetting.LoggerLevel) {
        std::fstream logfile;
        full_msg = DateUtils::getTimeWithFormat() + "[" + LoggerLevelToString[typeOfLog] + "] " + message;
        logfile.open(LogSetting.LoggerPathFile.c_str(), std::fstream::app | std::fstream::out);
        logfile << full_msg << endl;

        if (LogSetting.LoggerConsole){
        	cout << full_msg << endl;
        }
    }
	return full_msg;
}

bool validLogLevel(int log_level){
	return (log_level <= DEBUG && log_level >= ERROR);
}
