#include "Calendar.h"

const int NOT_LEAP_YEAR = 0;
const int LEAP_YEAR = 1;

const int NUM_OF_MONTHS = 12;
const int MAX_DAYS_IN_MONTH[2][12] = {
	//1   2   3   4   5   6   7   8   9  10  11  12		// Month
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},	// Non leap year
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}	// Leap year
	//1   2   3   4   5   6   7   8   9  10  11  12		// Month
};
const string MONTH[] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

const string MONTH_ABBR[] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

const int DAY_PER_WEEK = 7;
const string DAY[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};
const string DAY_ABBR[] = {
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat"
};