#include "timewiseclock.h"

TimeWiseClock::TimeWiseClock() {
	_date = QDate::currentDate();
	_time = QTime::currentTime();
}

TimeWiseClock::~TimeWiseClock()
{
}

QString TimeWiseClock::dateToString(){
	return _date.toString();
}

QString TimeWiseClock::timeToString(){
	return _time.toString();
}