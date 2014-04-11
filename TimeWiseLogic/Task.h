#pragma once

#include "Constants.h"
#include <string>
#include <algorithm>
#include "Date.h"
#include "ClockTime.h"
#include <assert.h>
#include "Parser.h"

class Task
{
public:
	Task(void);
	~Task(void);

	//getter functions
	int getIndex();
	std::string getDescription();
	Date* getEndDate();
	Date* getStartDate();
	ClockTime* getEndTime();
	ClockTime* getStartTime();
	TASK_STATUS getTaskStatus();
	std::string getTaskCategory();

	//setter functions
	void setIndex(int);
	void setDescription(std::string desc);
	void setCategory(std::string category);
	void setEndDate(Date* endDate);
	void setStartDate(Date* startDate);
	void setStartTime(ClockTime* startTime);
	void setEndTime(ClockTime* endTime);
	void setStatusAsDone();
	void setStatusasUndone();
	void setStatusAsOverdue();
	//check overdue
	bool checkOverdue();
	bool checkNewOverdue();
	bool hasKeyword(std::string keyword);
	bool hasDate(Date* date);
	bool hasCategory(std::string category);
	bool hasStatus(TASK_STATUS status);
	bool checkLater(Task* otherTask);
	bool checkClash(Task* task);

	bool checkClashDate(Task* task);

	bool checkTimeClashForDeadlineTask(Task* task);
	void setClash(bool clash);
	std::string toString();
	bool isClash();
	void resetClash();
	void setSchedule(Date* sDate,Date* eDate,ClockTime* sTime,ClockTime* eTime);
	bool isFloating();
	bool isSingleDate();
	bool isDoubleDate();
	void checkInvalidDate();
	void setDateBasedOnTime();
	void setTime();
	bool checkTimeClashForTimedTask(Task* task);
	bool withTime();
	void editSchedule(ClockTime* sTime,ClockTime* eTime);
	std::string getDayString();
	bool isSingleTime();
	bool isDoubleTime();
	bool hasStartDate();
	bool hasEndDate();
	bool hasStartTime();
	bool hasEndTime();
	void initializeTask();
	void resetPointers();
	void convertToLowerCase(std::string& keywordInLowerCase, std::string& taskInLowerCase);
	unsigned int findIndexOfKeywordInTask(std::string taskInLowerCase, std::string keywordInLowerCase);
	bool isValidIndex(unsigned int index);
protected:
	std::string _taskDescription;
	TASK_STATUS _taskStatus;
	std::string _category;
	int _taskIndex;
	bool _clashStatus;

	Date *_endDate;
	Date *_startDate;
	ClockTime *_startTime;
	ClockTime *_endTime;
	Parser _parser;



};