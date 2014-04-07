#include "Date.h"

// Constructors
Date::Date() {
	this->setDateAsToday();
}

Date::Date(int day, int month, int year) {
	this->setDate(day, month, year);
}

Date::Date(Date& src) {
	this->setDate(src._dayNumber, src._month, src._year);
}

// Destructors
Date::~Date() {
}

// Get & "Set by input" functions
int Date::getDay() {
	return _dayNumber;
}

int Date::getMonth(){
	return _month;
}

int Date::getYear() {
	return _year;
}

int Date::getWeekDay() {
	return _day;
}

string Date::getDayOfTheWeek() {
	return DAY_ABBR[_day];
}

void Date::setDate(int day, int month, int year) {
	if(month<1 || month>NUM_OF_MONTHS || year<1 || day<1) {
		throw InvalidDateTimeFormatException();
	} else {
		if(isLeapYear(year) == true && day > MAX_DAYS_IN_MONTH[LEAP_YEAR][month-1]) {
			throw InvalidDateTimeFormatException();
		} else if(isLeapYear(year)==false && day > MAX_DAYS_IN_MONTH[NOT_LEAP_YEAR][month-1]) {
			throw InvalidDateTimeFormatException();
		}
	}
	_dayNumber = day;
	_month = month;
	_year = year;
	_day=getDayFromDate(day,month,year);
}

// Set functions without input parameters
void Date::setDateAsToday() {
	time_t _currentTime;
	struct tm _timeNow ;

	_currentTime = time(0);   
	localtime_s(&_timeNow,&_currentTime);

	_dayNumber = _timeNow.tm_mday;
	_month = _timeNow.tm_mon + 1;
	_year = _timeNow.tm_year + 1900;
	_day = _timeNow.tm_wday;
}

void Date::setDateAsTomorrow() {
	setDateAsToday();
	(*this)++;
}

void Date::setDateAsDayAfterTomorrow() {
	setDateAsTomorrow();
	(*this)++;
}

// Normal member functions
TIMEDATE_STATUS Date::checkOverdue() {
	time_t _currentTime;
	struct tm _timeNow ;

	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisYear = _timeNow.tm_year + 1900;
	int thisMonth = _timeNow.tm_mon + 1;
	int todayDate = _timeNow.tm_mday;

	if(_year>thisYear) {
		return EARLIER;
	} else if(_year<thisYear) {
		return LATER;
	} else {
		if(_month>thisMonth) {
			return EARLIER;
		} else if(_month<thisMonth) {
			return LATER;
		} else {
			if(_dayNumber>todayDate) {
				return EARLIER;
			} else if(_dayNumber<todayDate) {
				return LATER;
			} else {
				return SAME;
			}
		}
	}
}

bool Date::compare(Date* date) {
	return (*this) == (*date);
}

TIMEDATE_STATUS Date::isLater(Date* otherDate) {
	if(otherDate==NULL) {
		return LATER;
	}
	if(_year>otherDate->_year) {
		return LATER;
	} else if(_year<otherDate->_year) {
		return EARLIER;
	} else {
		if(_month>otherDate->_month) {
			return LATER;
		} else if(_month<otherDate->_month) {
			return EARLIER;
		} else {
			if(_dayNumber>otherDate->_dayNumber) {
				return LATER;
			} else if(_dayNumber<otherDate->_dayNumber) {
				return EARLIER;
			} else {
				return SAME;
			}
		}
	}
}

int Date::leapYear() {
	return isLeapYear(_year);
}

string Date::toFormat() {
	ostringstream convert;
	string slash = "/";
	string dateInString;
	convert << _dayNumber << slash << _month << slash << _year;
	dateInString = convert.str();
	return dateInString;
}

string Date::toString() {
	ostringstream convert;
	string space = " ";
	convert << _year;
	string year=convert.str();
	year = year.substr(2);
	convert.str(string());
	string dateInString;
	convert << _dayNumber << space << MONTH_ABBR[_month-1];

	dateInString = convert.str();
	return dateInString;
}

// "Global" functions (Functions not related to objects)
int Date::getCurrentYear() {
	time_t _currentTime;
	struct tm _timeNow ;

	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisYear = _timeNow.tm_year + 1900;

	return thisYear;
}

int Date::getCurrentMonth() {
	time_t _currentTime;
	struct tm _timeNow ;

	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisMonth = _timeNow.tm_mon + 1;

	return thisMonth;
}

int Date::getCurrentDay() {
	time_t _currentTime;
	struct tm _timeNow ;

	_currentTime = time(0);   
	localtime_s( &_timeNow, &_currentTime ); // get local PC time

	int thisDay = _timeNow.tm_mday;

	return thisDay;
}

bool Date::isLeapYear(int year) {
	bool leapYear = false;

	if(year % 400 == 0) {
		leapYear = true;
	} else if(year % 100 == 0) {
		leapYear = false;
	} else if(year % 4 == 0) {
		leapYear = true;
	}
	return leapYear;
}

// Operators
Date Date::operator+(int num) {
	if(num<0) {
		return (*this) - (-num);
	}
	for(int i=0 ; i<num ; i++) {
		(*this)++;
	}
	return *this;
}

Date Date::operator-(int num) {
	if(num<0) {
		return (*this) + (-num);
	}
	for(int i=0 ; i<num ; i++) {
		(*this)--;
	}
	return *this;
}

Date& Date::operator++() {
	if(_dayNumber == MAX_DAYS_IN_MONTH[this->leapYear()][_month-1]) {
		_dayNumber = 1;
		if(_month == 12) {
			_month = 1;
			_year += 1;
		} else {
			_month += 1;
		}
	} else {
		_dayNumber += 1;
	}
	_day = (_day + 1) % 7;
	return *this;
}

Date Date::operator++(int) {
	Date original(*this);
	++(*this);
	return original;
}

Date& Date::operator--() {
	_dayNumber -= 1;
	if(_dayNumber == 0) {
		if(_month > 1) {
			_month -= 1;
			_dayNumber = MAX_DAYS_IN_MONTH[this->leapYear()][_month-1];
		} else {
			_year -= 1;
			_month = NUM_OF_MONTHS;
			_dayNumber = MAX_DAYS_IN_MONTH[this->leapYear()][11];
		}
	}
	_day = _day - 1;
	while(_day < 0) {
		_day += 7;
	}
	return *this;
}

Date Date::operator--(int) {
	Date original(*this);
	--(*this);
	return original;
}

bool Date::operator==(Date b) {
	bool same = false;

	if( this->_year == b._year && this->_month == b._month && this->_dayNumber == b._dayNumber) {
		same = true;
	}

	return same;
}

bool Date::operator>(Date b) {
	bool larger = false;

	if( this->_year > b._year ||
		this->_year == b._year && this->_month > b._month || 
		this->_year == b._year && this->_month == b._month && this->_dayNumber > b._dayNumber) {
			larger = true;
	}

	return larger;
}

bool Date::operator<(Date b) {
	bool smaller = false;

	if( this->_year < b._year ||
		this->_year == b._year && this->_month < b._month || 
		this->_year == b._year && this->_month == b._month && this->_dayNumber < b._dayNumber) {
			smaller = true;
	}

	return smaller;
}

bool Date::operator>=(Date b) {
	return ( *this > b || *this == b );
}

bool Date::operator<=(Date b) {
	return ( *this < b || *this == b );
}

Date Date::operator+=(int num) {
	*this = *this + num;
	return *this;
}

Date Date::operator-=(int num) {
	*this = *this - num;
	return *this;
}

int Date::getDayFromDate(int day,int month,int year)
{
	tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = 12;    //  To avoid any doubts about summer time, etc.
	mktime( &timeStruct );
	return timeStruct.tm_wday;  //  0...6 for Sunday...Saturday
}

bool Date::isToday(){
	if(_dayNumber==getCurrentDay()&&_month==getCurrentMonth()&&_year==getCurrentYear()){
		return true;
	}
	return false;
}

bool Date::isTomorrow(){
	time_t tomorrow = time(0) + 24*60*60;
	struct tm _timeNow ;

	localtime_s( &_timeNow, &tomorrow);
	int day = _timeNow.tm_mday;
	int month = _timeNow.tm_mon + 1;
	int year = _timeNow.tm_year + 1900;
	if(_dayNumber==day&&_month==month&&_year==year){
		return true;
	}
	return false;
}

void Date::setNextDay(){
	(*this)++;
}
