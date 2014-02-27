#pragma once

#include <string>
#include <ctime>
class ClockTime
{
public:
	ClockTime();
	ClockTime(int time);	
	~ClockTime(void);
	void setTimeNow(int time);
	std::string getTimeInString();
	bool checkOverdueTime();

private:
	int _time;

};