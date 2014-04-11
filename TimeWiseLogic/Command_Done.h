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
	void addDoneIndex(int);
	void setPreviousScreen(DISPLAY_TYPE* screen);

private:
	std::vector<Task*> _doneTasks;
	std::vector<unsigned int> _doneTaskIndex;
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE  _previousScreen;
	std::string   _lastCmdCalled;
};

