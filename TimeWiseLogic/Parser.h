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

class Parser
{
private:
	Date dateFunction;
public:
	Parser(void);
	~Parser(void);

	CMD_TYPE determineCommandType(std::string);
	HEADER determineHeaderType(std::string);
	
	// Parser functions
	vector<int> extractDate(string, int);
	vector<int> extractTime(string, int);
	bool isDateFormat(std::string);
	bool isTimeFormat(std::string);
	bool isCategory(std::string&);
	bool isPriority(std::string&);
	bool containsDay(std::string);
	TASK_TYPE determineTaskType(std::string trimmedInput);
	bool is24HourTimeFormat(std::string);
	bool isPreposition(std::string);
	TASK_STATUS getTaskStatus(std::string);
	PRIORITY getPriority(std::string input);

	ClockTime* createTime(string time);
	ClockTime* createTime(int time);

	Date* createDate(std::string date);

	// String functions
	string strval(int);

	string getFirstWord(std::string);
	string removeFirstWord(std::string);
	string replaceWord(std::string, std::string, std::string);
	string convertToLowerCase(string str);
	bool stringExists(string, string);
	bool isAllNumbers(std::string);
	int toNum(std::string);
	vector<string> splitBySpace(string input);
	vector<string> explode(char delimiter, string input);
	string getStringAfter(char, std::string);
	string getStringBefore(char, std::string);
	void removeWhiteSpaces(std::string&);
	string trim(string);
};

#endif
