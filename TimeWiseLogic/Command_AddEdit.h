#pragma once
#include "command_add.h"
class Command_AddEdit :
	public Command_Add
{
public:
	Command_AddEdit(void);
	~Command_AddEdit(void);

	bool execute(TaskList&);
	bool undo(TaskList&);
private:
	Task* _deletedTask;
	std::string _lastCmdCalled;
};

