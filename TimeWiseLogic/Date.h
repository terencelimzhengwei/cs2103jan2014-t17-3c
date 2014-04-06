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

	int getDay();
	int getMonth();
	int getYear();
	int getWeekDay();
	string getDayOfTheWeek();
	void setDate(int day, int month, int year);

	void setDateAsToday();
	void setDateAsTomorrow();

	TIMEDATE_STATUS checkOverdue();
	bool compare(Date* date);
	TIMEDATE_STATUS isLater(Date* otherDate);
	int leapYear();
	std::string toFormat();
	std::string toString();
	
	static int isLeapYear(int);
	static int getCurrentYear();
	static int getCurrentMonth();
	static int getCurrentDay();

	Date operator+(int);
	Date operator-(int);
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	bool operator==(Date);
	bool operator>(Date);
	bool operator<(Date);
	bool operator>=(Date);
	bool operator<=(Date);
	Date operator+=(int);
	Date operator-=(int);

private:

	int _dayNumber;
	int _month;
	int _year;
	int _day;
};
#endif