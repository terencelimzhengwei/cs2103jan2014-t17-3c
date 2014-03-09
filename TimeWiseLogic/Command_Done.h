#pragma once
#include "command_undoable.h"
class Command_Done : public Command_Undoable{
public:
	Command_Done(void);
	~Command_Done(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setCompletedIndex(unsigned int index);

private:
	unsigned int _taskIndex;
	Task* _task;

};

