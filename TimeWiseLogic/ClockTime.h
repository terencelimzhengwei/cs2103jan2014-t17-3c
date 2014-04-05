#pragma once

#include <string>
#include <assert.h>
#include <ctime>
#include <sstream>
#include <exception>
#include "Exceptions.h"
#include "Constants.h"

class ClockTime
{
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

private:
	int _time;
};