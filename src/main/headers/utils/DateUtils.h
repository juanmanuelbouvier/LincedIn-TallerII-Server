#ifndef DATE_UTILS_H_
#define DATE_UTILS_H_

#include <string>

using namespace std;

class DateUtils {
public:
	static const string dateTimeFormat;
	static const string getTimeWithFormat(string Format = "[%Y/%m/%d %X]");
	static const string parseDate(string date, string date_format, string toFormat = dateTimeFormat);
	static int timestamp();
};

#endif /* DATE_UTILS_H_ */
