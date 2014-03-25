#pragma once
#include "Command.h"
class Command_Clear:public Command{
public:
	Command_Clear(void);
	Command_Clear(CLEAR_TYPE clearType);
	Command_Clear(DISPLAY_TYPE displayType);
	~Command_Clear(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
private:
	std::vector<Task*> _deletedTasks;
	std::string _lastCmdCalled;
	CLEAR_TYPE _clearType;
	DISPLAY_TYPE _displayType;
	void clearCompletedTasks(TaskList& tasklist);
	void clearUncompletedTasks(TaskList& tasklist);
	void clearAll(TaskList& tasklist);
	void undoCompletedTasks(TaskList& tasklist);
	void undoUncompletedTasks(TaskList& tasklist);
	void clearScreen(TaskList& tasklist);
	void undoAll(TaskList& tasklist);



};

