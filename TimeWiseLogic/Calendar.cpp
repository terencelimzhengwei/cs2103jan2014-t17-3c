#include "Calendar.h"

const std::string DAY[7] = {"sunday", "monday", "tuesday", "wednesday", 
					   "thursday", "friday", "saturday" };
const std::string DAY_ABBR[7] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat" };
const int MAX_DAYS_IN_MONTH[2][12] = { {31,28,31,30,31,30,31,31,30,31,30,31},  // Non leap year
{31,29,31,30,31,30,31,31,30,31,30,31} };// leap year
const std::string MONTH_ABBR[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
const int NUM_OF_MONTHS = 12;
const int LEAP_YEAR = 1;
const int NOT_LEAP_YEAR = 0;