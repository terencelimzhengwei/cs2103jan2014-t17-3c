//@author A0121023H
#ifndef DATE_H
#define DATE_H

#pragma once

#include <ctime>
#include <sstream>
#include <string>
#include "Calendar.h"
#include "Constants.h"
#include "Exceptions.h"

class Date{
public:
	Date(void);
	Date(Date& date);
	Date(int day, int month, int year);
	~Date(void);

	int getDay();
	int getMonth();
	int getYear();
	int getWeekday();
	string getDayOfTheWeek();
	void setDate(int day, int month, int year);

	void setDateAsToday();
	void setDateAsTomorrow();

	TIMEDATE_STATUS checkOverdue();
	bool compare(Date* date);
	bool isToday();
	TIMEDATE_STATUS isLater(Date* otherDate);
	int leapYear();
	std::string toFormat();
	std::string toString();

	static bool isLeapYear(int);
	static int getCurrentYear();
	static int getCurrentMonth();
	static int getCurrentDay();
	static int getCurrentWeekday();
	static int getDayFromDate(int,int,int);

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
	bool isTomorrow();
	void setDateAsDayAfterTomorrow();
	void setNextDay();

private:
	int _day;
	int _month;
	int _year;
	int _weekday;
};
#endif