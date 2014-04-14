//@author A0097277M
#ifndef TIMEWISELOGIC_H
#define TIMEWISELOGIC_H

#pragma once

#include "CommandCreator.h"
#include "CommandManager.h"
#include "Constants.h"
#include "Logger.h"
#include "Storage.h"
#include "TaskList.h"

//********************************************************************************
// This class acts as the facade class linking GUI to the rest of the other components.
// Its main usage is to take in input from the user from the GUI and processing the command
// It also returns a tasklist for the GUI to populate the display screen depending on the
// screen to display.
//********************************************************************************
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