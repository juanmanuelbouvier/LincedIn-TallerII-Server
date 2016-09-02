#include "Util.h"

const string getTimeWithFormat(string Format) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    const char* format = Format.c_str();
    strftime(buf, sizeof(buf), format, &tstruct);
    return buf;
}