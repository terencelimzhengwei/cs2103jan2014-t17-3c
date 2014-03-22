#pragma once

#include "Constants.h"
#include <string>
#include <algorithm>
#include "Date.h"
#include "ClockTime.h"
#include <assert.h>

class Task
{
public:
	Task(void);
	~Task(void);
	
	//getter functions
	unsigned long long getIndex();
	std::string getDescription();
	Date* getEndDate();
	Date* getStartDate();
	ClockTime* getEndTime();
	ClockTime* getStartTime();
	TASK_STATUS getTaskStatus();
	std::string getTaskCategory();
	PRIORITY getPriority();
	

	//setter functions
	void setIndex(unsigned long long);
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

	//check overdue
	bool checkOverdue();
	bool hasKeyword(std::string keyword);
	bool hasPriority(PRIORITY priority);
	bool hasDate(Date* date);
	bool hasCategory(std::string category);
	bool hasStatus(TASK_STATUS status);
	bool checkLater(Task* otherTask);

protected:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	PRIORITY _taskPriority;
	std::string _category;
	unsigned long long _taskIndex;

	Date *_endDate;
	Date *_startDate;
	ClockTime *_startTime;
	ClockTime *_endTime;
};