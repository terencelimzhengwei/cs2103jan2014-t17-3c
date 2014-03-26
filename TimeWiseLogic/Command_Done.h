#pragma once
#include "command.h"
class Command_Done : public Command{
public:
	Command_Done(void);
	~Command_Done(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setCompletedIndex(int index);
	void setDisplayScreen(DISPLAY_TYPE& screen);

private:
	int _taskIndex;
	Task* _task;
	DISPLAY_TYPE* _displayType;
	std::string _lastCmdCalled;

};

