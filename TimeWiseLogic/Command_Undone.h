#pragma once
#include "command_undoable.h"
class Command_Undone :
	public Command_Undoable
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
};

