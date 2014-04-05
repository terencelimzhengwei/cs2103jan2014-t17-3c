#pragma once
#include "Command.h"
class Command_Clear:public Command{
public:
	Command_Clear(void);
	Command_Clear(CLEAR_TYPE clearType);
	~Command_Clear(void);

	bool execute(TaskList& tasklist, std::string& feedback);
	bool undo(TaskList& tasklist);
	void setDisplayScreen(DISPLAY_TYPE displayType);
private:
	void clearCompletedTasks(TaskList& tasklist);
	void clearUncompletedTasks(TaskList& tasklist);
	void clearAll(TaskList& tasklist);
	void undoCompletedTasks(TaskList& tasklist);
	void undoUncompletedTasks(TaskList& tasklist);

	void repopulateFilterList(TaskList &tasklist);
	void repopulateSearchList(TaskList &tasklist);

	void clearScreen(TaskList& tasklist);
	void saveSearchedTasks(TaskList &tasklist);

	void undoAll(TaskList& tasklist);
	void saveFilteredTasks(TaskList &tasklist);

	DISPLAY_TYPE _displayScreen;
	std::vector<Task*> _deletedUndoneTasks;
	std::vector<Task*> _deletedDoneTasks;
	std::vector<Task*> _deletedSearchedTasks;
	std::vector<Task*> _deletedFilteredTasks;
	std::string _lastCmdCalled;
	CLEAR_TYPE _clearType;
};

