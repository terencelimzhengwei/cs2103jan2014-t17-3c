#pragma once

#ifndef COMMAND_H
#define COMMAND_H

// TiMEWiSE Command Base Class
//I dont really understand what exactly the flag methods do
//Will update once I pick it up
#include <list>
#include <string>
#include "Date.h"
#include "ClockTime.h"
#include "Constants.h"
#include "TaskList.h"

class Command
{
public:
	Command(void);
	virtual ~Command(void);
	virtual bool execute(TaskList& tasklist)=0;
	virtual bool undo(TaskList& tasklist)=0;
	CMD_TYPE getType();
protected:
	CMD_TYPE _type;
};
#endif