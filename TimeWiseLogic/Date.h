#ifndef DATE_H
#define DATE_H

#pragma once

#include <string>
#include <ctime>
#include <sstream>
#include "Calendar.h"
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
	bool checkOverdue();
	std::string toString();
private:
	time_t _currentTime;
	struct tm _timeNow ;

	int _dayNumber;
	int _month;
	int _year;
	int _day;
	std::string _dayInString;

	void setDateAsToday();
	void setDate(int day, int month, int year);
};
#endif