#pragma once
#include "Command_Undoable.h"
class Command_Clear:public Command_Undoable{
public:
	Command_Clear(void);
	~Command_Clear(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
private:
	std::vector<Task*> _deletedTasks;
	std::string _lastCmdCalled;
};

