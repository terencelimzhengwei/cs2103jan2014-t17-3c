#include "timewiseclock.h"

TimeWiseClock::TimeWiseClock() {
	date = QDate::currentDate();
	time = QTime::currentTime();
}

TimeWiseClock::~TimeWiseClock()
{
}

QString TimeWiseClock::dateToString(){
	return date.toString();
}

QString TimeWiseClock::timeToString(){
	return time.toString();
}