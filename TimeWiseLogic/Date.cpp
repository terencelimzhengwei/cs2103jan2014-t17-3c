#include "Date.h"

Date::Date(){
}

Date::Date(int day, int month, int year){
	if(month<=0||month>12||year<=0||day<=0){
		throw InvalidDateTimeFormatException();
	}else{
		int leapYear =isLeapYear();
		if(_dayNumber>MAX_DAYS_IN_MONTH[leapYear][month]){
			throw InvalidDateTimeFormatException();
			//LeapYear invalid exception
		}
	}
	_dayNumber = day;
	_month = month;
	_year = year;
}

Date::Date(Date& date){
	if(date._month<=0||date._month>12||date._year<=0||date._year<=0){
		throw InvalidDateTimeFormatException();
	}else{
		int leapYear =isLeapYear();
		if(_dayNumber>MAX_DAYS_IN_MONTH[leapYear][date._month]){
			throw InvalidDateTimeFormatException();
			//LeapYear invalid exception
		}
	}
	_dayNumber = date._dayNumber;
	_month = date._month;
	_year =date._year;
	_day = date._day;
	_dayInString = date._dayInString;
}

Date::~Date(){
}

void Date::setDate(int day, int month, int year){
	if(month<=0||month>12||year<=0||day<=0){
		throw InvalidDateTimeFormatException();
	}else{
		int leapYear =isLeapYear();
		if(_dayNumber>MAX_DAYS_IN_MONTH[leapYear][month]){
			throw InvalidDateTimeFormatException();
			//LeapYear invalid exception
		}
	}
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

void Date::setDateAsTomorrow() {
	setDateAsToday();
	(*this)++;
}

TIMEDATE_STATUS Date::checkOverdue()
{
	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisYear = _timeNow.tm_year + 1900;
	int thisMonth = _timeNow.tm_mon + 1;
	int todayDate = _timeNow.tm_mday;

	if(_year>thisYear){
		return EARLIER;
	}else if(_year<thisYear){
		return LATER;
	}else{
		if(_month>thisMonth){
			return EARLIER;
		}else if(_month<thisMonth){
			return LATER;
		}else{
			if(_dayNumber>todayDate){
				return EARLIER;
			}else if(_dayNumber<todayDate){
				return LATER;
			}else{
				return SAME;
			}
		}
	}

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

std::string Date::toFormat(){
	std::ostringstream convert;
	std::string slash = "/";
	std::string dateInString;
	convert<<_dayNumber<<slash<<_month<<slash<<_year;
	dateInString=convert.str();
	return dateInString;
}

int Date::getCurrentYear(){
	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisYear = _timeNow.tm_year + 1900;

	return thisYear;
}

int Date::getCurrentMonth(){
	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisMonth = _timeNow.tm_mon + 1;

	return thisMonth;
}


int Date::getCurrentDay(){
	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisDay = _timeNow.tm_mday;

	return thisDay;
}

bool Date::compare(Date* date){
	if(date==NULL){
		return false;
	}
	int day = date->getDayNumber();
	int month = date->getMonth();
	int year = date->getYear();
	if(day==_dayNumber&&month==_month&&year==_year){
		return true;
	}
	return false;
}

int Date::isLeapYear(){
	int yearType = NOT_LEAP_YEAR;

	if ( _year % 400 == 0){
		yearType = LEAP_YEAR;
	}
	else if( _year % 100 == 0){
		yearType = NOT_LEAP_YEAR;
	}
	else if ( _year % 4 == 0){
		yearType = LEAP_YEAR;
	}
	return yearType;
}

Date Date::operator++(int) {
	Date original(*this);
	if(getMonth() == 1 || getMonth() == 3|| getMonth() == 5 || getMonth() == 7 || getMonth() == 8 || getMonth() == 12) {
		if(getDayNumber() == 31) {
			_dayNumber = 1;
			if(getMonth() == 12) {
				_month = 1;
				_year = getYear() + 1;
			} else {
				_month = getMonth() + 1;
				_year = getYear();
			}	
		} else {
			_month = getMonth();
			_dayNumber = getDayNumber() + 1;
			_year = getYear();
		}
	} else if (getMonth() == 2) {
		if(getDayNumber()== 29) {
			_dayNumber = 1;
			_month = 3;
			_year = getYear();
		} else {
			_month = getMonth();
			_dayNumber = getDayNumber() + 1;
			_year = getYear();
		}
	} else if (getMonth() == 4 || getMonth() == 6|| getMonth() == 9 || getMonth() == 10 || getMonth() == 11) {
		if(getDayNumber()== 30) {
			_dayNumber = 1;
			_month = getMonth() + 1;
			_year = getYear();
		} else {
			_month = getMonth();
			_dayNumber = getDayNumber() + 1;
			_year = getYear();
		}
	}

	_day = (_day + 1) % 7;
	_dayInString = DAY[_day];
	return original;
}