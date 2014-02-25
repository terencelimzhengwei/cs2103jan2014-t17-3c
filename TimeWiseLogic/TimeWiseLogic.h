#pragma once

#include "Constants.h"
#include "TaskList.h"
#include "Storage.h"
#include "Parser.h"
#include "CommandProcessor.h"

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
	CommandProcessor _commandProcessor;
	Parser _parser;
	TaskList _taskList;
	Storage _storage;

	//Command _cmd;
	//Feedback _feedback;

};
