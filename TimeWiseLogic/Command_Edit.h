#pragma once
#include "Command.h"


class Command_Edit : public Command {
public:
	Command_Edit();
	~Command_Edit(void);

	//setter for fields
	void setIndex(int);
	void setDescription(std::string);
	void setPriority(PRIORITY);
	void setCategory(std::string);
	void setStartDate(Date);
	void setEndDate(Date);
	void setStartTime(ClockTime);
	void setEndTime(ClockTime);
	void setTaskStatus(TASK_STATUS);
	void setTaskType(TASK_TYPE);

	virtual bool execute(TaskList& tasklist);
	virtual bool undo(TaskList& taskList);

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

