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
	
	//getter functions
	//int getIndex();
	std::string getDescription();
	Date getDate();
	ClockTime getEndTime();
	ClockTime getStartTime();
	TASK_STATUS getTaskStatus();
	std::string getTaskCategory();
	

	//setter functions
	//void setIndex(int)
	void setDescription(std::string desc);
	void setPriority(PRIORITY taskPriority);
	void setCategory(std::string category);
	void setDate(Date date);
	void setStartTime(ClockTime startTime);
	void setEndTime(ClockTime endTime);
	void setStatusAsDone();
	void setStatusAsOverdue();
	void setTaskType(TASK_TYPE type);

	//check overdue
	bool checkOverdue();

protected:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	PRIORITY _taskPriority;
	std::string _category;
	int _taskIndex;

	Date _date;
	ClockTime _startTime;
	ClockTime _endTime;


};