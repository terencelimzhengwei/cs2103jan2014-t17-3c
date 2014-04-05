#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
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
	static vector<int> extractDate(string, int);
	static vector<int> extractTime(string, int);
	static bool isDateFormat(std::string);
	static bool isTimeFormat(std::string);
	static bool isCategory(std::string&);
	static bool isPreposition(std::string);
	static TASK_STATUS getTaskStatus(std::string);

	static ClockTime* createTime(string time);
	static ClockTime* createTime(int time);

	static Date* createDate(std::string date);

	// String functions
	static vector<string> explode(char delimiter, string input);
	static bool isAllNumbers(std::string);
	static string replaceWord(std::string, std::string, std::string);
	static bool stringExists(string, string);
	static string strToLower(string str);
	static string strVal(int);
	static int toNum(string);
	static string trim(string);

	// String shortcut functions
	static string getFirstWord(string);
	static string removeFirstWord(string);

	// Deprecated string functions
	static void removeWhiteSpaces(string&);
	static vector<string> splitBySpace(string input);

	// Unused functions
	// bool containsDay(std::string);
	// HEADER determineHeaderType(std::string);
};

#endif
