#pragma once
#include "Command.h"


class Command_Edit : public Command {
public:
	Command_Edit();
	~Command_Edit(void);
	//getter for fields
	std::string	getDescription();
	unsigned long long  getIndex();
	Date getDate();
	ClockTime getStartTime();
	ClockTime getEndTime();
	PRIORITY getTaskPriority();
	TASK_STATUS getTaskStatus();
	TASK_TYPE getTaskType();
	//setter for fields
	void setIndex(int);
	void setDescription(std::string);
	void setPriority(PRIORITY);
	void setCategory(std::string);
	void setDate(Date);
	void setStartTime(ClockTime);
	void setEndTime(ClockTime);
	void setTaskStatus(TASK_STATUS);
	void setTaskType(TASK_TYPE);
};

