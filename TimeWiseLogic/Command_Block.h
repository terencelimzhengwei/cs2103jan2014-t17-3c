#pragma once
#include "command.h"
#include "BlockSchedule.h"
class Command_Block :
	public Command
{
public:
	Command_Block(void);
	~Command_Block(void);
	void setDescription(std::string description);
	void setPriority(PRIORITY);
	void setCategory(std::string);
	void setTaskType(TASK_TYPE);
	void setPreviousScreen(DISPLAY_TYPE*);
	void addSchedule(Date* startDate, Date* endDate, ClockTime* startTime, ClockTime* endTime);

	virtual bool execute(TaskList&,std::string&);
	virtual bool undo(TaskList&);

private:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	PRIORITY _taskPriority;
	std::string _category;
	std::string _userInput;
	std::string _lastCmdCalled;
	std::vector<BlockSchedule> blockTimings;
	std::vector<Task*> _addedTaskList;
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _previousScreen;
};
