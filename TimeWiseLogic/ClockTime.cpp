#include "ClockTime.h"


ClockTime::ClockTime(){
}


ClockTime::~ClockTime(void){
}

std::string ClockTime::getTimeInString(){
	return _timeInString;
}

void ClockTime::setTimeNow(std::string timeNow)
{
	_timeInString=timeNow;
}
