#pragma once
#include "Command.h"
#include <stack>

class Command_Delete : public Command{
public:
	Command_Delete();
	~Command_Delete(void);
	void setDeletionIndex(unsigned int index);
	void setDeletionString(std::string deletionString);

	virtual bool execute(TaskList& tasklist);
	virtual bool undo(TaskList& taskList);

private:
	Task* _taskDeleted;
	unsigned int _deletionIndex;
	std::string _deletionString;
	std::string _lastCmdCalled;
};

