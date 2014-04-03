#pragma once
#include "command.h"
class Command_Redo :
	public Command
{
public:
	Command_Redo(void);
	~Command_Redo(void);
	virtual bool execute(TaskList& tasklist, std::string& feedback);
	virtual bool undo(TaskList& taskList);
};

