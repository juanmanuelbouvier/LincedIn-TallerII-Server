#include <utils/DateUtils.h>
#include <iomanip>
#include <ctime>
#include <sstream>

const string DateUtils::dateTimeFormat = "%Y-%m-%d %H:%M:%S";


const string DateUtils::getTimeWithFormat(string format) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    const char* format_to_strf = format.c_str();
    strftime(buf, sizeof(buf), format_to_strf, &tstruct);
    return buf;
}


int DateUtils::timestamp(){
    string now = DateUtils::getTimeWithFormat("%s");
    return atoi(now.c_str());
}

const string DateUtils::parseDate(string date, string date_format, string toFormat) {
    tm t = {};
    istringstream stream1(date);
    stream1 >> get_time(&t, date_format.c_str());
    stringstream stream2;
    stream2 << put_time(&t, toFormat.c_str());
    return ( stream1.fail() ) ? "" : stream2.str();
}
