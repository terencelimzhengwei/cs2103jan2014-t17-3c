#include "timewiseclock.h"

//@author A0097330H
TimeWiseClock::TimeWiseClock() {
	_date = QDate::currentDate();
	_time = QTime::currentTime();
}

TimeWiseClock::~TimeWiseClock() {
}

QString TimeWiseClock::dateToString(){
	return _date.toString();
}

QString TimeWiseClock::timeToString(){
	return _time.toString();
}