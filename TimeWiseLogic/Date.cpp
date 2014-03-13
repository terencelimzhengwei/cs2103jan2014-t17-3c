#include "Date.h"

Date::Date(){
}

Date::Date(int day, int month, int year){
	_dayNumber=day;
	_month=month;
	_year=year;
}

Date::Date(Date& date){
	_dayNumber = date._dayNumber;
	_month = date._month;
	_year =date._year;
	_day = date._day;
	_dayInString = date._dayInString;
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

std::string Date::getDayOfTheWeek(){
	return _dayInString;
}

std::string Date::toString(){
	std::ostringstream convert;
	std::string space = " ";
	convert<<_year;
	std::string year=convert.str();
	year = year.substr(2);
	convert.str(std::string());
	std::string dateInString;
	convert<<_dayNumber<<space<<MONTH_ABBR[_month-1]<<space<<year;
	
	dateInString=convert.str();
	return dateInString;
}

TIMEDATE_STATUS Date::isLater(Date* otherDate)
{
	if(otherDate==NULL){
		return LATER;
	}
	if(_year>otherDate->_year){
		return LATER;
	}else if(_year<otherDate->_year){
		return EARLIER;
	}else{
		if(_month>otherDate->_month){
			return LATER;
		}else if(_month<otherDate->_month){
			return EARLIER;
		}else{
			if(_dayNumber>otherDate->_dayNumber){
				return LATER;
			}else if(_dayNumber<otherDate->_dayNumber){
				return EARLIER;
			}else{
				return SAME;
			}
		}
	}
}

int Date::getDayNumber(){
	return _dayNumber;
}

int Date::getMonth(){
	return _month;
}

int Date::getYear(){
	return _year;
}
