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
private:
	Date dateFunction;
public:
	Parser();
	~Parser();

	CMD_TYPE determineCommandType(std::string);
	
	// Parser functions
	vector<int> extractDate(string, int);
	vector<int> extractTime(string, int);
	bool isDateFormat(std::string);
	bool isTimeFormat(std::string);
	bool isCategory(std::string&);
	bool containsDay(std::string);
	TASK_TYPE determineTaskType(std::string trimmedInput);
	bool isPreposition(std::string);
	TASK_STATUS getTaskStatus(std::string);

	ClockTime* createTime(string time);
	ClockTime* createTime(int time);

	Date* createDate(std::string date);

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
	string getFirstWord(string);
	string removeFirstWord(string);

	// Deprecated string functions
	void removeWhiteSpaces(string&);
	vector<string> splitBySpace(string input);

	// Unused functions
	// HEADER determineHeaderType(std::string);
};

#endif
