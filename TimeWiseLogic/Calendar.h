#ifndef _CALENDAR_H
#define _CALENDAR_H
//@author A0099938
//********************************************************************************
// This class stores all the constants regarding date: days in week
// days in month, months, years.
//********************************************************************************
#include <string>
using namespace std;

enum Day{MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
enum Month{JAN, FEB, MAR, APR, MAY, JUN, JULY, AUGUST, SEPT, OCT, NOV, DEC};

extern const int NOT_LEAP_YEAR;
extern const int LEAP_YEAR;

extern const int NUM_OF_MONTHS;				// two set of arrays to differentiate the leap year
extern const int MAX_DAYS_IN_MONTH[2][12];	// contains the number of maximum days of a month in a year
extern const string MONTH[];
extern const string MONTH_ABBR[];			// contains the abbreviation of month arranger in order
extern const int MONTH_DIGIT[];

extern const int DAY_PER_WEEK;
extern const string DAY[];					// contains the day in string arranged in order from sunday to monday
extern const string DAY_ABBR[];			// contains the abbreviation of day arranged in order as above	

#endif