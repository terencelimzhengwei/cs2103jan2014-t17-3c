//@author A0097277M
#ifndef TASK_H
#define TASK_H

#pragma once

#include <string>
#include <algorithm>
#include <assert.h>

#include "Constants.h"
#include "ClockTime.h"
#include "Date.h"
#include "Parser.h"

//********************************************************************************
// This class is used to store the details of user Task
//********************************************************************************
class Task{
public:
	Task(void);
	~Task(void);

	//Getter functions
	std::string getDescription();
	Date* getEndDate();
	Date* getStartDate();
	ClockTime* getEndTime();
	ClockTime* getStartTime();
	TASK_STATUS getTaskStatus();
	std::string getTaskCategory();

	//Setter functions
	void setDescription(std::string desc);
	void setCategory(std::string category);
	void setEndDate(Date* endDate);
	void setStartDate(Date* startDate);
	void setStartTime(ClockTime* startTime);
	void setEndTime(ClockTime* endTime);
	void setStatusAsDone();
	void setStatusasUndone();
	void setStatusAsOverdue();

	//Overdue Checker
	bool checkOverdue();
	bool checkNewOverdue();

	//Clash Checker
	bool checkClash(Task* task);
	void setClash(bool clash);
	bool isClash();
	void resetClash();


	//Check for presence of attribute for filter
	bool hasKeyword(std::string keyword);
	bool hasDate(Date* date);
	bool hasCategory(std::string category);

	//For sorting task by date
	bool checkLater(Task* otherTask);

	//Schedule Setter
	void setSchedule(Date* sDate,Date* eDate,ClockTime* sTime,ClockTime* eTime);
	void editSchedule(ClockTime* sTime,ClockTime* eTime);

	//Get Task Day in String
	std::string getDayString();

protected:
	std::string _taskDescription;
	TASK_STATUS _taskStatus;
	std::string _category;
	bool _clashStatus;

	Date *_endDate;
	Date *_startDate;
	ClockTime *_startTime;
	ClockTime *_endTime;
	Parser _parser;

	//Initializer Helper Functions
	void initializeTask();

	//Destructor helper functions
	void resetPointers();

	//Clash Helper Functions
	void getTimeOfBothTaskInInt(int& sTime, int& eTime, int& othersTime, int& othereTime, Task* task);
	bool isSingleTime();
	bool isDoubleTime();
	bool hasStartDate();
	bool hasEndDate();
	bool hasStartTime();
	bool hasEndTime();
	bool checkClashDate(Task* task);
	bool checkTimeClashForDeadlineTask(Task* task);
	bool isFloating();
	bool isSingleDate();
	bool isDoubleDate();
	void checkClashSingleDateDoubleDate(Task* task, bool& clash);
	void checkClashDoubleDateSingleDate(Task* task, bool& clash);
	void checkClashForSingleDate(Task* task, bool& clash);
	void checkClashForDoubleDate(Task* task, bool& clash);

	//Helper functions to help in search
	void convertToLowerCase(std::string& keywordInLowerCase, std::string& taskInLowerCase);
	unsigned int findIndexOfKeywordInString(std::string taskInLowerCase, std::string keywordInLowerCase);
	bool isValidIndex(unsigned int index);

	//Assist in adding schedule
	void setTime();
	bool withTime();
	void checkInvalidDate();
	void setDateBasedOnTime();
	void setDateForDeadlineTaskAccordingToTime();
	void setDateForFloatingTask();
	void setEndDateAccordingToStartTime();
	void setStartAndEndDateAcordingToTime();
	bool startTimeLaterThanEndTime();
	void setEndDateAccordingToEndTime();
};
#endif