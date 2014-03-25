#pragma once
#include "Command.h"
#include <stack>

class Command_Delete : public Command{
public:
	Command_Delete(void);
	~Command_Delete(void);
	void setDeletionIndex(unsigned int index);
	void setDeletionString(std::string deletionString);
	void setDisplayScreen(DISPLAY_TYPE display);

	virtual bool execute(TaskList& tasklist);
	virtual bool undo(TaskList& taskList);

private:
	Task* _taskDeleted;
	unsigned int _deletionIndex;
	std::string _deletionString;
	std::string _lastCmdCalled;
	DISPLAY_TYPE _displayType;
};

