//@author A0121023H
#include "ClockTime.h"

ClockTime::ClockTime() {
}

ClockTime::ClockTime(int time) {
	this->setTime(time);
}

ClockTime::ClockTime(ClockTime& src) {
	this->setTime(src._time);
}

ClockTime::~ClockTime() {
}

void ClockTime::setTime(int time) {
	if(time<ZERO || hour(time)>MAX_HOUR || minute(time)>MAX_MINUTE) {
		throw InvalidDateTimeFormatException();
	}
	_time = time;
}

bool ClockTime::checkOverdueTime() {
	bool hasElapsed;
	struct tm today;
	time_t currentTime = time(ZERO);	// get local time
	int hr  = _time / TIME_DIVISOR,
		min = _time % TIME_DIVISOR;

	localtime_s( &today, &currentTime); // update tm struct to be local date and time

	if( hr < today.tm_hour ) {
		hasElapsed = true;
	} else if ( hr == today.tm_hour && min <= today.tm_min) {
		hasElapsed = true; 
	} else{
		hasElapsed = false;
	}
	return hasElapsed;
}

std::string ClockTime::toString() {
	std::ostringstream stream;
	int timeInt = _time;
	stream<<_time;
	std::string timeInString;
	timeInString = stream.str();

	switch(timeInString.size()) {
	case 1:
		if(timeInString[ZERO]=='0') {
			return "0000";
		} else {
			return "000"+timeInString;
		}
		break;
	case 2:
		return "00" + timeInString;
	case 3:
		return "0" + timeInString;
	default:
		return timeInString;
	}
}

TIMEDATE_STATUS ClockTime::isLater(ClockTime* otherTime) {
	if(otherTime==NULL) {
		return LATER;
	} else if(_time>otherTime->getTime()) {
		return LATER;
	} else if(_time==otherTime->getTime()) {
		return SAME;
	}
	return EARLIER;
}

int ClockTime::getTime() {
	return _time;
}

// Operators

bool ClockTime::operator==(ClockTime b) {
	return this->_time == b._time;
}

bool ClockTime::operator>(ClockTime b) {
	return this->_time > b._time;
}

bool ClockTime::operator<(ClockTime b) {
	return this->_time < b._time;
}

bool ClockTime::operator>=(ClockTime b) {
	return this->_time >= b._time;
}

bool ClockTime::operator<=(ClockTime b) {
	return this->_time <= b._time;
}