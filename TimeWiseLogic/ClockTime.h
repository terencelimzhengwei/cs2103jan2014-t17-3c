#pragma once

#include <string>
#include <ctime>
#include <sstream>
class ClockTime
{
public:
	ClockTime();
	ClockTime(int time);
	ClockTime(ClockTime& _time);
	~ClockTime(void);
	void setTimeNow(int time);
	std::string toString();
	bool checkOverdueTime();

private:
	int _time;
};