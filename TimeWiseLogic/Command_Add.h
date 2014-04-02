#pragma once
#include "Command.h"

class Command_Add: public Command {
public:
	Command_Add();
	~Command_Add(void);

	//setter for fields
	void setDescription(std::string);
	void setPriority(PRIORITY);
	void setCategory(std::string);
	void setEndDate(Date& date);
	void setStartDate(Date&);
	void setStartTime(ClockTime&);
	void setEndTime(ClockTime&);
	void setTaskType(TASK_TYPE);
	void setPreviousScreen(DISPLAY_TYPE*);

	//checker for fields
	bool hasEndDate();
	bool hasStartDate();
	bool hasStartTime();
	bool hasEndTime();

	virtual bool execute(TaskList&);
	virtual bool undo(TaskList&);

protected:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	PRIORITY _taskPriority;
	std::string _category;
	std::string _userInput;
	Date* _startDate;
	Date* _endDate;
	ClockTime* _startTime;
	ClockTime* _endTime;
	std::string _lastCmdCalled;

	Task* _addedTask;
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _previousScreen;

};
