#pragma once
#include "Command_Undoable.h"
#include <stack>


class Command_Edit : public Command_Undoable {
public:
	Command_Edit();
	~Command_Edit(void);

	//setter for fields
	void setDescription(std::string);
	void setPriority(PRIORITY);
	void setCategory(std::string);
	void setStartDate(Date);
	void setIndex(unsigned int);
	void setEndDate(Date);
	void setStartTime(ClockTime);
	void setEndTime(ClockTime);
	void setHeader(std::string);

	virtual bool execute(TaskList& tasklist);
	virtual bool undo(TaskList& taskList);

private:
	std::string _taskDescription;
	PRIORITY _taskPriority;
	std::string _category;
	Date _startDate;
	Date _endDate;
	ClockTime _startTime;
	ClockTime _endTime;

	Task* _taskEdited;
	Task _originalTask;
	unsigned int _taskIndex;
	std::string _header;
};

