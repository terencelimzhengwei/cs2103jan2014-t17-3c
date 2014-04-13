#pragma once

#ifndef COMMAND_H
#define COMMAND_H

#include <list>
#include <string>
#include <assert.h>
#include "Date.h"
#include "ClockTime.h"
#include "Constants.h"
#include "TaskList.h"
#include "Exceptions.h"
// @author A0097277M
/*
 *=======================
 
	Command Base class
 
 *=======================
 */

class Command
{
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