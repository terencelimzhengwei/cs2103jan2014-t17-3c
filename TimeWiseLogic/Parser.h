#pragma once
#ifndef PARSER_H
#define PARSER_H

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

	static CMD_TYPE determineCommandType(std::string);
	
	// Parser functions
	static vector<int> extractDate(string);
	static vector<int> extractDate(string, int);
	static void extractDateTime(string, string&, vector<Date>&, vector<ClockTime>&);

	static vector<int> extractTime(string, int);
	static bool isDateFormat(std::string);
	static bool isTimeFormat(std::string);
	static bool isCategory(std::string&);
	static bool isPreposition(std::string);
	static TASK_STATUS getTaskStatus(std::string);

	static ClockTime* createTime(string time);
	static ClockTime* createTime(int time);

	static Date* createDate(std::string date);

	static bool isDate(string);
	static bool isDate(string, Date&);
	static bool isTime(string);
	static bool isTime(string, ClockTime&);

	static string regexDateTime(string);
	static bool isValidConvertedDate(string&, Date&);
	static bool isValidConvertedTime(string&, ClockTime&);

	// String functions
	static vector<string> explode(char delimiter, string input);
	static bool isAllNumbers(std::string);
	static bool stringExists(string, string);

	static string strIReplace(string, string, string);

	static string strReplace(string, string, string);
	static vector<string> strReplace(string, string, vector<string>);
	static string strReplace(vector<string>, string, string);
	static string strReplace(vector<string>, vector<string>, string);
	static vector<string> strReplace(vector<string>, vector<string>, vector<string>);

	static int strSearch(string, string);
	static int strSearch(string, string, int);

	static string strTruncate(string);

	static string strToLower(string str);
	static string strVal(int);
	static vector<string> strVal(vector<int>);
	static int toNum(string);
	static string trim(string);

	// String shortcut functions
	static string getFirstWord(string);
	static string removeFirstWord(string);
	static string getLastWord(string);
	static string removeLastWord(string);

	// Deprecated string functions
	static void removeWhiteSpaces(string&);
	static vector<string> splitBySpace(string input);
};

#endif
