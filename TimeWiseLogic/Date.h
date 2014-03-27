#ifndef DATE_H
#define DATE_H

#pragma once

#include <string>
#include <ctime>
#include <sstream>
#include "Exceptions.h"
#include "Calendar.h"
#include "Constants.h"
//#include "Parser.h"

class Date
{
public:
	Date(void);
	Date(Date& date);
	Date(int day, int month, int year);
	~Date(void);

	int getDayNumber();
	std::string getDayOfTheWeek();
	int getMonth();
	int getYear();
	TIMEDATE_STATUS checkOverdue();
	TIMEDATE_STATUS isLater(Date* otherDate);
	std::string toString();
	std::string toFormat();
	int isLeapYear();

	int getCurrentYear();
	int getCurrentMonth();
	int getCurrentDay();
	void setDateAsTomorrow();
	bool compare(Date* date);
	void setDate(int day, int month, int year);


private:
	time_t _currentTime;
	struct tm _timeNow ;

	int _dayNumber;
	int _month;
	int _year;
	int _day;
	std::string _dayInString;
	void setDateAsToday();
};
#endif