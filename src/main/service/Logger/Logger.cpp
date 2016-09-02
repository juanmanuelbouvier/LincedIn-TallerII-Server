#include "Logger.h"

struct LoggerSetting LogSetting;

const string LoggerLevelToString[] = {"ERROR", "WARNING", "INFO", "DEBUG"};


void _LoggerInitLogMessage(){
	// Nueva apertura del logfile con un mensaje de bienvenida
	string version = to_string(LincedInServer_VERSION_MAJOR) + "." + to_string(LincedInServer_VERSION_MINOR);
	Log("------------------------------------------------------------------",INFO);
	Log("\t\tNew Run of: LincedInAppServer | Version: " + version,INFO);
	Log("------------------------------------------------------------------",INFO);
}


void LoggerInit(int level, bool log_console, string path){
	LogSetting.LoggerLevel = level;
	LogSetting.LoggerConsole = log_console;
	LogSetting.LoggerPathFile = path;
    _LoggerInitLogMessage();
}

void Log(string message, LogLevel typeOfLog){
    if (typeOfLog <= LogSetting.LoggerLevel) {
        std::fstream logfile;
        string full_msg = getTimeWithFormat() + LoggerLevelToString[typeOfLog] + " : " + message;
        logfile.open(LogSetting.LoggerPathFile.c_str(), std::fstream::app | std::fstream::out);
        logfile << full_msg << endl;

        if (LogSetting.LoggerConsole){
        	cout << full_msg << endl;
        }
    }
}
