#pragma once
#include "command.h"
//**********************************************************************
// This class is responsible for changing the status  an individual task
// specified by its index.
//**********************************************************************
class Command_Undone :
	public Command
{
public:
	Command_Undone(void);
	~Command_Undone(void);
	bool execute(TaskList&, std::string&);
	bool undo(TaskList&);
	void setUncompletedIndex(int);
	void setDisplayScreen(DISPLAY_TYPE);

private:
	int _taskIndex;
	Task* _task;
	DISPLAY_TYPE _displayType;
};

