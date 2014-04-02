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
	if(getCurrentMonth() == 1 || getCurrentMonth() == 3|| getCurrentMonth() == 5||
		getCurrentMonth() == 7|| getCurrentMonth() == 8|| getCurrentMonth() == 12) {
			if(getCurrentDay() == 31) {
				_dayNumber = 1;
				if(getCurrentMonth() == 12) {
					_month = 1;
					_year = getCurrentYear() + 1;
				} else {
					_month = getCurrentMonth() + 1;
					_year = getCurrentYear();
				}	
			} else {
				_month = getCurrentMonth();
				_dayNumber = getCurrentDay() + 1;
				_year = getCurrentYear();
			}
	} else if (getCurrentMonth() == 2) {
		if(getCurrentDay()== 29) {
			_dayNumber = 1;
			_month = 3;
			_year = getCurrentYear();
		} else {
			_month = getCurrentMonth();
			_dayNumber = getCurrentDay() + 1;
			_year = getCurrentYear();
		}
	} else if (getCurrentMonth() == 4 || getCurrentMonth() == 6|| getCurrentMonth() == 9||
		getCurrentMonth() == 10|| getCurrentMonth() == 11) {
			if(getCurrentDay()== 30) {
				_dayNumber = 1;
				_month = getCurrentMonth() + 1;
				_year = getCurrentYear();
			} else {
				_month = getCurrentMonth();
				_dayNumber = getCurrentDay() + 1;
				_year = getCurrentYear();
			}
	}

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
