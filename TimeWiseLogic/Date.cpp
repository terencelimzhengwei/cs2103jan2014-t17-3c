#include "Date.h"

Date::Date(){
}

Date::Date(int day, int month, int year){
	_dayNumber=day;
	_month=month;
	_year=year;
}

Date::~Date(){
}

void Date::setDate(int day, int month, int year){
	_dayNumber=day;
	_month=month;
	_year=year;
}
void Date::setDateAsToday(){
	_currentTime = time(0);   
	localtime_s(&_timeNow,&_currentTime);

	_dayNumber = _timeNow.tm_mday;
	_month = _timeNow.tm_mon + 1;
	_year = _timeNow.tm_year + 1900;
	_day = _timeNow.tm_wday;
	_dayInString = DAY[_day];
}

bool Date::checkOverdue(){
	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisYear = _timeNow.tm_year + 1900;
	int thisMonth = _timeNow.tm_mon + 1;
	int todayDate = _timeNow.tm_mday;
	bool overdue = false;

	if( _year < thisYear){
		overdue = true;
	}
	else if( _year == thisYear && _month < thisMonth){
		overdue = true;
	}
	else if( _year == thisYear && _month == thisMonth && _dayNumber < todayDate){
		overdue = true;
	}

	return overdue;

}
