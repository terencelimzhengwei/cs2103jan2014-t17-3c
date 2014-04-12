#pragma once
#ifndef TIMEWISELOGIC_H
#define TIMEWISELOGIC_H

#include "Constants.h"
#include "TaskList.h"
#include "Logger.h"
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
	DISPLAY_TYPE getScreenToDisplay();

private:
	CommandCreator _creator ;
	TaskList _taskList;
	Storage _storage;
	CommandManager *_manager;
	Logger* _logger;

	Command* _cmd;
	std::string _feedback;
	std::string _userInput;

	DISPLAY_TYPE _displayType;

	void initLogic();
	bool parseCommand(std::string commandLine);
	bool emptyCommandLine(std::string commandLine);

};
#endif