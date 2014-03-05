#pragma once
#include "Command.h"

class Command_Delete : public Command{
public:
	Command_Delete();
	~Command_Delete(void);
	void setDeletionIndex(int index);
	void setDeletionString(std::string deletionString);

	virtual bool execute(TaskList& tasklist);
	virtual bool undo(TaskList& taskList);

private:
	int _deletionIndex;
	std::string _deletionString;
};

