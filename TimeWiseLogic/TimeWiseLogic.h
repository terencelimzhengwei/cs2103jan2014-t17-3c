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
	DISPLAY_TYPE getScreenToDisplay();


private:
	CommandCreator _creator ;
	TaskList _taskList;
	Storage _storage;
	CommandManager *_manager;

	Command* _cmd;
	std::string _feedback;

	DISPLAY_TYPE _displayType;

	void initLogic();
	DISPLAY_TYPE setScreenToDisplay(Command* cmd);
	bool parseCommand(std::string commandLine);


};
#endif