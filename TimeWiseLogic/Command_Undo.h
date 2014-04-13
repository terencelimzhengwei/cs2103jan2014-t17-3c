#ifndef COMMAND_UNDO_H
#define COMMAND_UNDO_H

#pragma once

//********************************************************************************
// This class calls for Undo in Command Manger to execute undo in previously
// executed command
//********************************************************************************
// @author A0097277M
#include "command.h"
class Command_Undo :
	public Command
{
public:
	Command_Undo(void);
	~Command_Undo(void);
	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&, std::string&);
};
#endif

