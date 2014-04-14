//@author A0121023H
#ifndef PARSER_H
#define PARSER_H

#pragma once

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <regex>
#include "ClockTime.h"
#include "Date.h"
#include "Calendar.h"
using namespace std;
class Parser {
public:
	Parser();
	~Parser();

	static CMD_TYPE determineCommandType(string);
	static TASK_STATUS getTaskStatus(string);
	static bool isCategory(string);
	static bool isPreposition(string);
	static string removePunctuation(string);

	// Date and time related functions
	static Date* createDate(string);
	static ClockTime* createTime(string);
	static void extractDateTime(string, string&, vector<Date>&, vector<ClockTime>&);
	static bool isDate(string);
	static bool isDate(string, Date&);
	static bool isTime(string);
	static bool isTime(string, ClockTime&);
	static bool isValidConvertedDate(string&);
	static bool isValidConvertedDate(string&, Date&);
	static bool isValidConvertedTime(string&);
	static bool isValidConvertedTime(string&, ClockTime&);
	static string markupDateTime(string);
	
	// String processing functions
	static vector<string> explode(char, string);
	static bool isAllDigit(string);
	static string strConcat(vector<string>);
	static string strConcat(vector<string>, unsigned int, unsigned int);
	static string strIReplace(string, string, string);
	static string strToLower(string);
	static string strReplace(string, string, string);
	static vector<string> strReplace(string, string, vector<string>);
	static int strSearch(string, string);
	static int strSearch(string, string, int);
	static string strTruncate(string);
	static string strVal(int);
	static vector<string> strVal(vector<int>);
	static int toInt(string);
	static string trim(string);

	static string getFirstWord(string);
	static string removeFirstWord(string);
	static string getLastWord(string);
	static string removeLastWord(string);
	static vector<string> splitBySpace(string);
};

#endif
