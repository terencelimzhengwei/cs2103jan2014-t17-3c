//@author A0097277M
#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <assert.h>
#include <list>
#include <string>
#include "ClockTime.h"
#include "Constants.h"
#include "Date.h"
#include "Exceptions.h"
#include "TaskList.h"
//***************************************************************************
//
// Command Base Class
//
//***************************************************************************
class Command{
public:
	//Constructor & Destructor
	Command(void);
	virtual ~Command(void);

	//Get the type of command
	CMD_TYPE getType();

	//virtual execute & undo methods for use as part of the command design pattern
	virtual bool execute(TaskList& tasklist, std::string& feedback)=0;
	virtual bool undo(TaskList& tasklist, std::string& feedback)=0;
protected:
	//Attributes
	CMD_TYPE _type;
};
#endif