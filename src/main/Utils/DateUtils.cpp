#include "DateUtils.h"

/**
 * Get time string with especific format.<BR>
 * To view format read "`man strftime`",<BR>
 * Default is: '[%Y/%m/%d %X]'<BR>
 *  ej. [2016/09/07 08:42:49]
 */
const string DateUtils::getTimeWithFormat(string format) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    const char* format_to_strf = format.c_str();
    strftime(buf, sizeof(buf), format_to_strf, &tstruct);
    return buf;
}
