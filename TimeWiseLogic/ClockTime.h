//@author A0121023H
#pragma once

#include <string>
#include <assert.h>
#include <ctime>
#include <sstream>
#include <exception>
#include "Exceptions.h"
#include "Constants.h"

#define hour(time) time / TIME_DIVISOR
#define minute(time) time % TIME_DIVISOR

class ClockTime{
public:
	ClockTime();
	ClockTime(int time);
	ClockTime(ClockTime& _time);

	~ClockTime();

	void setTime(int time);
	int getTime();

	std::string toString();

	bool checkOverdueTime();
	TIMEDATE_STATUS isLater(ClockTime* otherTime);
	
	bool operator==(ClockTime);
	bool operator>(ClockTime);
	bool operator<(ClockTime);
	bool operator>=(ClockTime);
	bool operator<=(ClockTime);

private:
	int _time;
};