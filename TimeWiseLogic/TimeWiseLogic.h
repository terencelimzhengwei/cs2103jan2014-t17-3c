#pragma once
#ifndef TIMEWISELOGIC_H
#define TIMEWISELOGIC_H

#include "Constants.h"
#include "TaskList.h"
#include "Storage.h"
#include "Parser.h"
#include "CommandManager.h"

class TimeWiseLogic
{
public:
	TimeWiseLogic(void);
	~TimeWiseLogic(void);

	void initLogic();
	TaskList getTaskList();
	std::string processCommand(std::string commandLine);
	bool parseCommand(std::string commandLine);


private:
	Parser _parser;
	TaskList _taskList;
	Storage _storage;
	CommandManager *_manager;

	Command* _cmd;
	std::string _feedback;

};
#endif