#pragma once

#include "Constants.h"
#include <string>
#include "Date.h"
#include "ClockTime.h"

class Task
{
public:
	Task(void);
	~Task(void);
	std::string getDescription();
	void addDescription(std::string desc);
	void addPriority(PRIORITY taskPriority);
	void addCategory(std::string category);
private:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	PRIORITY _taskPriority;
	std::string _category;
	unsigned long long _taskIndex;
};