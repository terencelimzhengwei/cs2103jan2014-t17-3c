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
	PRIORITY getPriority();	

	//setter functions
	void setIndex(int);
	void setDescription(std::string desc);
	void setPriority(PRIORITY taskPriority);
	void setCategory(std::string category);
	void setEndDate(Date& endDate);
	void setStartDate(Date& startDate);
	void setStartTime(ClockTime& startTime);
	void setEndTime(ClockTime& endTime);
	void setStatusAsDone();
	void setStatusasUndone();
	void setStatusAsOverdue();
	void setTaskType(TASK_TYPE type);
	void setEditStatus(bool value);

	//check overdue
	bool checkOverdue();
	bool checkNewOverdue();
	bool hasKeyword(std::string keyword);
	bool hasPriority(PRIORITY priority);
	bool hasDate(Date* date);
	bool hasCategory(std::string category);
	bool hasStatus(TASK_STATUS status);
	bool checkLater(Task* otherTask);
	bool checkClash(Task* task);
	bool checkEditStatus();
	std::string toString();

protected:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	PRIORITY _taskPriority;
	std::string _category;
	int _taskIndex;

	Date *_endDate;
	Date *_startDate;
	ClockTime *_startTime;
	ClockTime *_endTime;
	bool _editStatus;
	Parser _parser;

};