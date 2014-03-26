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
	void setUncompletedIndex(int index);
	void setDisplayScreen(DISPLAY_TYPE screen);

private:
	int _taskIndex;
	Task* _task;
	DISPLAY_TYPE _displayType;
};

