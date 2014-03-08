#pragma once
#include "Command.h"

class Command_Undoable:public Command{

public:
	Command_Undoable(void);
	~Command_Undoable(void);

	virtual bool undo(TaskList& tasklist)=0;
};

