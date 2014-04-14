#ifndef COMMAND_CLEAR_H
#define COMMAND_CLEAR_H
// @author A0097277M
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

	void saveSearchedTasks(TaskList&);
	void saveFilteredTasks(TaskList&);

	void clearScreen(TaskList&, std::string&);
	void clearCompletedTasks(TaskList&);
	void clearUncompletedTasks(TaskList&);
	void clearAll(TaskList&);

	void undoCompletedTasks(TaskList&, std::string&);
	void undoUncompletedTasks(TaskList&, std::string&);

	void repopulateFilterList(TaskList&);
	void repopulateSearchList(TaskList&);

	void undoScreenTasks(TaskList& tasklist, std::string& feedback);
	void undoFilteredTasks(TaskList& tasklist, std::string& feedback);
	void undoSearchedTasks(TaskList& tasklist, std::string& feedback);
	void undoAll(TaskList&, std::string&);

	//Helper Functions
	void createFeedback(std::string taskFeedback,std::string& feedback);
	void permanantlyDeleteTasks();
	void lastCmdCalledIs(std::string cmd);
	bool wasUndone();
	bool wasExecuted();

	//Attributes
	DISPLAY_TYPE _displayScreen;
	CLEAR_TYPE _clearType;
	//Vector to store pointers of deletedTasks so that command can be undone
	std::vector<Task*> _deletedUndoneTasks;
	std::vector<Task*> _deletedDoneTasks;
	std::vector<Task*> _deletedSearchedTasks;
	std::vector<Task*> _deletedFilteredTasks;
	std::string _lastCmdCalled;
};
#endif
