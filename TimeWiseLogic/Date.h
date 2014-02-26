#pragma once

#include <string>
#include <ctime>
#include "Calendar.h"
#include "Parser.h"

class Date
{
public:
	Date(void);
	~Date(void);
private:
	int _dayNumber;
	int _month;
	int _year;

	Day _day;
	std::string _dayInString;

	Parser _parser;
};

