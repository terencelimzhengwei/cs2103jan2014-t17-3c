#pragma once
#include "command.h"
class Command_Undo :
	public Command
{
public:
	Command_Undo(void);
	~Command_Undo(void);
	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&);
};

