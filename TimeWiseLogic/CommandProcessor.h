#pragma once

#ifndef _CommandProcessor_H
#define _CommandProcessor_H

#include "Command.h"
#include "TaskList.h"
class CommandProcessor
{
public:
	CommandProcessor(void);
	~CommandProcessor(void);
	void executeCommand(Command);
	Task formTask(Command);
	void setTaskList(TaskList& taskList);
private:
	TaskList* _list;
};
#endif