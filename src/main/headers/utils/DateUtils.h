#ifndef DATE_UTILS_H_
#define DATE_UTILS_H_

#include <string>

using namespace std;

class DateUtils {
public:
	/**
	 * Datetime constant string YYYY-mm-dd HH:MM:SS
	 */
	static const string dateTimeFormat;

	/**
	 * Get actual time string with especific format.<BR>
	 * To view format read "`man strftime`",<BR>
	 * Default is: '[%Y/%m/%d %X]'<BR>
	 *  ej. [2016/09/07 08:42:49]
	 */
	static const string getTimeWithFormat(string Format = "[%Y/%m/%d %X]");


	/**
	 * Parse time with specific format.
	 * To view format codes read "`man strftime`",<BR>
	 * @param The date to be parsed.
	 * @param Format specified in format codes of date.
	 * @param Format to be parsed using format codes. Default is dateTimeFormat.
	 * @return A string parsed. If date or format of date is invalid, return empty string.
	 * ej. parseDate("16/2/2012","%d/%m/%Y","Day: %d - Month %m - Year %Y | %H:%M:%S") ==> Day: 16 - Month 2 - Year 2012 | 00:00:00
	 */
	static const string parseDate(string date, string date_format, string toFormat = dateTimeFormat);

	/**
	 * Get actual time in seconds since the epoch (1970)<BR>
	 * Equivalent to getTimeWithFormat("%s");
	 */
	static int timestamp();
};

#endif /* DATE_UTILS_H_ */
