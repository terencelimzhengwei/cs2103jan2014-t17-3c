#pragma once
#include "command.h"
class Command_Undone :
	public Command
{
public:
	Command_Undone(void);
	~Command_Undone(void);
	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setUncompletedIndex(unsigned int index);

private:
	unsigned int _taskIndex;
	Task* _task;
	DISPLAY_TYPE _displayType;
};

