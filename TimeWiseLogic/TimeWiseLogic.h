#pragma once
#ifndef TIMEWISELOGIC_H
#define TIMEWISELOGIC_H

#include "Constants.h"
#include "TaskList.h"
#include "Storage.h"
#include "CommandCreator.h"
#include "CommandManager.h"

class TimeWiseLogic
{
public:
	TimeWiseLogic(void);
	~TimeWiseLogic(void);

	TaskList getTaskList();
	std::string processCommand(std::string commandLine);
	bool parseCommand(std::string commandLine);


private:
	CommandCreator _creator ;
	TaskList _taskList;
	Storage _storage;
	CommandManager *_manager;

	Command* _cmd;
	std::string _feedback;

	void initLogic();

};
#endif