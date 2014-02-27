#ifndef DATE_H
#define DATE_H

#pragma once

#include <string>
#include <ctime>
#include "Calendar.h"
#include "Parser.h"

class Date
{
public:
	Date(void);
	~Date(void);

	int getDayNumber();
	int getMonth();
	int getYear();

private:
	time_t _currentTime;
	struct tm _timeNow ;

	int _dayNumber;
	int _month;
	int _year;
	int _day;
	std::string _dayInString;

	Parser _parser;

	void setDateAsToday();
	void setDate(int day, int month, int year);
};
#endif