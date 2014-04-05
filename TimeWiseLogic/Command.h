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

class Command
{
public:
	Command(void);
	virtual ~Command(void);
	virtual bool execute(TaskList& tasklist, std::string& feedback)=0;
	virtual bool undo(TaskList& tasklist, std::string& feedback)=0;
	CMD_TYPE getType();
protected:
	CMD_TYPE _type;
};
#endif