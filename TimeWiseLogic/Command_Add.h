#pragma once
#include "Command.h"

class Command_Add: public Command {
public:
	Command_Add();
	~Command_Add(void);

	void setDescription(std::string);
	void setCategory(std::string);
	void setEndDate(Date&);
	void setStartDate(Date&);
	void setStartTime(ClockTime&);
	void setEndTime(ClockTime&);
	void setTaskType(TASK_TYPE);
	void setPreviousScreen(DISPLAY_TYPE*);

	virtual bool execute(TaskList&,std::string&);
	virtual bool undo(TaskList&, std::string&);

protected:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	std::string _category;
	std::string _userInput;
	std::string _lastCmdCalled;

	Date* _startDate;
	Date* _endDate;
	ClockTime* _startTime;
	ClockTime* _endTime;


	Task* _addedTask;
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _previousScreen;

};
