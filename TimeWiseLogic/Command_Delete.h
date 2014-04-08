#pragma once
#include "Command.h"
#include <stack>

//************************************************************
// This class is responsible for deleting an individual task
// specified by its index
//************************************************************
class Command_Delete : public Command{
public:
	Command_Delete(void);
	~Command_Delete(void);
	void setDeletionIndex(int);
	void setDeletionString(std::string);
	void setDisplayScreen(DISPLAY_TYPE display);

	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&, std::string&);

private:
	Task* _taskDeleted;
	unsigned int _deletionIndex;
	std::string _deletionString;
	std::string _lastCmdCalled;
	DISPLAY_TYPE _displayType;
};

