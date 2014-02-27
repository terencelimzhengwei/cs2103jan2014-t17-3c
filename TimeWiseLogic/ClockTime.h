#pragma once

#include <string>
#include <ctime>
class ClockTime
{
public:
	ClockTime();
	
	~ClockTime(void);
	void setTimeNow(std::string timeNow);
	std::string getTimeInString();
private:
	std::string _timeInString;

	time_t currentTime;
	struct tm _timeNow;

};