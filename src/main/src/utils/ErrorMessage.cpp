#include <utils/ErrorMessage.h>

using namespace std;

string ErrorMessage::summary(){
	string summary = "";

	for (std::map<string,string>::iterator it=error.begin(); it!=error.end(); ++it)
		summary += it->first + " => " + it->second + ". ";

	return summary;
}

void ErrorMessage::addError(string key, string error){
	this->error[key] = error;
}

string ErrorMessage::getError(string key){
	return error[key];
}

bool ErrorMessage::empty(){
	return error.empty();
}

