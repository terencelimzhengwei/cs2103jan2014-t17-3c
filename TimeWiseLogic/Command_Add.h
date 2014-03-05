#pragma once
#include "Command.h"

class Command_Add: public Command {
public:
	Command_Add();
	~Command_Add(void);

	//setter for fields
	void setIndex(int);
	void setDescription(std::string);
	void setPriority(PRIORITY);
	void setCategory(std::string);
	void setEndDate(Date);
	void setStartDate(Date);
	void setStartTime(ClockTime);
	void setEndTime(ClockTime);
	//void setTaskStatus(TASK_STATUS);
	void setTaskType(TASK_TYPE);

	virtual bool execute(TaskList&);
	virtual bool undo(TaskList&);

private:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	PRIORITY _taskPriority;
	std::string _category;
	int _taskIndex;
	Date _startDate;
	Date _endDate;
	ClockTime _startTime;
	ClockTime _endTime;
};
