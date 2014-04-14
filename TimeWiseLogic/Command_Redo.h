//@author A0097277M
#ifndef COMMAND_REDO_H
#define COMMAND_REDO_H

#pragma once
#include "command.h"
//********************************************************************************
// This class calls for Redo in Command Manger to execute redo in previously
// undone command
//********************************************************************************

class Command_Redo :public Command{
public:
	Command_Redo(void);
	~Command_Redo(void);
	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&, std::string&);
};
#endif

