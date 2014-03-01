#pragma once

#ifndef _CommandProcessor_H
#define _CommandProcessor_H

#include "Command_Add.h"
#include "TaskList.h"
class CommandProcessor
{
public:
	CommandProcessor(void);
	~CommandProcessor(void);
	void executeCommand(Command_Add);
	Task formTask(Command_Add);
	void setTaskList(TaskList& taskList);
private:
	TaskList* _list;
};
#endif