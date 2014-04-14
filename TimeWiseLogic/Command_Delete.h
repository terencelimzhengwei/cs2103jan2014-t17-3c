#ifndef COMMAND_DELETE_H
#define COMMAND_DELETE_H

#pragma once

#include "Command.h"
#include <stack>

//************************************************************
// This class is responsible for deleting an individual task
// specified by its index
//************************************************************
// @author A0097277M
class Command_Delete : public Command{
public:
	Command_Delete(void);
	~Command_Delete(void);
	//adds Deletion Index to be deleted
	void addDeletionIndex(int);
	//Setting Display so Command knows which tasklist to delete from
	void setDisplayScreen(DISPLAY_TYPE display);
	
	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&, std::string&);

private:
	//Functions to assist in executing/undoing/redoing
	void redo(TaskList& taskList);
	void deleteTasks(TaskList& taskList);

	void backUpTasks(TaskList &taskList);

	void backUpFilteredTasks(TaskList &taskList);

	void backUpSearchedTasks(TaskList &taskList);

	void backUpCompletedTasks(TaskList &taskList);

	void backUpMainTasks(TaskList &taskList);

	//For destruction of tasks. Task will only be destructed in either commandDelete or commandClear
	void permanantlyDeleteTask();

	//Helper Functions
	bool wasUndone();
	bool wasExecuted();
	void lastCmdCalledIs(std::string cmd);
	void createFeedback(std::string taskFeedback,std::string& feedback);
	void deleteMainTasks(TaskList& taskList);
	void deleteCompletedTasks(TaskList& taskList);
	void deleteSearchedTasks(TaskList& taskList);
	void deleteFilterTasks(TaskList& taskList);
	std::string _deletionString;
	std::string _lastCmdCalled;
	DISPLAY_TYPE _displayType;
	std::vector<Task*> _deletedTasks;
	std::vector<unsigned int> _deletedTaskIndex;
};
#endif
