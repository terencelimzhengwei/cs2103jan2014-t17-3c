#pragma once
#include "Command.h"
//********************************************************************************
// This class is responsible for deleting multiple tasks at once depending on the
// the display screen that the user is currently working with.
// It contains methods which allows users to clear:
// 1. all tasks from the schedule
// 2. all completed tasks 
// 3. all uncompleted tasks
// 4. all tasks that contain the same search key word.
// 5. all tasks that are in the same filtered list
//********************************************************************************
class Command_Clear:public Command{
public:
	Command_Clear(void);
	Command_Clear(CLEAR_TYPE);
	~Command_Clear(void);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);
	void setDisplayScreen(DISPLAY_TYPE);
private:
	void clearCompletedTasks(TaskList&);
	void clearUncompletedTasks(TaskList&);
	void clearAll(TaskList&);

	void undoCompletedTasks(TaskList&, std::string&);
	void undoUncompletedTasks(TaskList&, std::string&);

	void repopulateFilterList(TaskList&);
	void repopulateSearchList(TaskList&);

	void clearScreen(TaskList&, std::string&);
	void saveSearchedTasks(TaskList&);

	void undoAll(TaskList&, std::string&);
	void saveFilteredTasks(TaskList&);

	DISPLAY_TYPE _displayScreen;
	CLEAR_TYPE _clearType;

	std::vector<Task*> _deletedUndoneTasks;
	std::vector<Task*> _deletedDoneTasks;
	std::vector<Task*> _deletedSearchedTasks;
	std::vector<Task*> _deletedFilteredTasks;
	std::string _lastCmdCalled;
};

