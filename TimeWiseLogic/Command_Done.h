#pragma once
#include "command.h"
class Command_Done : public Command{
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
