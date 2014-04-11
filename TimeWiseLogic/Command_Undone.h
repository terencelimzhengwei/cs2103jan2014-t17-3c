#pragma once
#include "command.h"
//**********************************************************************
// This class is responsible for changing the status  an individual task
// specified by its index.
//**********************************************************************
class Command_Undone :
	public Command
{
public:
	Command_Undone(void);
	~Command_Undone(void);
	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);
	void addUndoneIndex(int index);
	void setDisplayScreen(DISPLAY_TYPE);

private:
	std::vector<Task*> _undoneTasks;
	std::vector<unsigned int> _undoneTaskIndex;
	DISPLAY_TYPE _displayType;
	std::string _lastCmdCalled;
};

