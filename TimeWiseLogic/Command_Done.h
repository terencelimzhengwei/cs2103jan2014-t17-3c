#pragma once
#include "command.h"
//********************************************************************************
// This class contains methods which are responsible for changing the status of
// an individual task from UNDONE to DONE.
// The individual task is specified by its index.
//********************************************************************************
class Command_Done : public Command{
public:
	Command_Done(void);
	~Command_Done(void);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);
	void setCompletedIndex(int);
	void setDisplayScreen(DISPLAY_TYPE);

private:
	int _taskIndex;
	Task* _task;
	DISPLAY_TYPE _displayType;
	std::string _lastCmdCalled;

};

