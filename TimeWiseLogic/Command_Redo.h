#ifndef COMMAND_REDO_H
#define COMMAND_REDO_H
// @author A0097277M
#pragma once

//********************************************************************************
// This class calls for Redo in Command Manger to execute redo in previously
// undone command
//********************************************************************************
#include "command.h"
class Command_Redo :public Command
{
public:
	Command_Redo(void);
	~Command_Redo(void);
	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&, std::string&);
};
#endif

