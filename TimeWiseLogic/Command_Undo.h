#pragma once
#include "command.h"
class Command_Undo :
	public Command
{
public:
	Command_Undo(void);
	~Command_Undo(void);
	virtual bool execute(TaskList& tasklist, std::string& feedback);
	virtual bool undo(TaskList& taskList);
};

