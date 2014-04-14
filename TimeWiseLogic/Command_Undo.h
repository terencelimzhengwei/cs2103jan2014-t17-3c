//@author A0097277M
#ifndef COMMAND_UNDO_H
#define COMMAND_UNDO_H

#pragma once
#include "command.h"
//********************************************************************************
// This class calls for Undo in Command Manger to execute undo in previously
// executed command
//********************************************************************************

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

