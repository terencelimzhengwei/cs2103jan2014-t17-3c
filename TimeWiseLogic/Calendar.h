#ifndef _CALENDAR_H
#define _CALENDAR_H

#include <string>

enum Day{MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,SUNDAY};

extern const std::string DAY[7];			// contains the day in string arranged in order from sunday to monday
extern const std::string DAY_ABBR[7];		// contains the abbreviation of day arranged in order as above	
extern const int MAX_DAYS_IN_MONTH[2][12];  // contains the number of maximum days of a month in a year
extern const int NUM_OF_MONTHS;				// two set of arrays to differentiate the leap year
extern const int LEAP_YEAR;
extern const int NOT_LEAP_YEAR;

#endif