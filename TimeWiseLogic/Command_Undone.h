#ifndef COMMAND_UNDONE_H
#define COMMAND_UNDONE_H
// @author A0097277M
#pragma once

#include "command.h"
//**********************************************************************
// This class is responsible for changing the status  an individual task
// specified by its index.
//**********************************************************************
class Command_Undone :
	public Command
{
public:
	Command_Undone(void);
	~Command_Undone(void);
	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);
	void addUndoneIndex(int index);
	void setPreviousScreen(DISPLAY_TYPE* screen);

private:
	std::vector<Task*> _undoneTasks;
	std::vector<unsigned int> _undoneTaskIndex;
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _previousScreen;
	std::string _lastCmdCalled;

	void setIndexToBoldInGUI(TaskList& tasklist);
	void saveTasks(TaskList& taskList);
	void setTasksAsUndone(TaskList& tasklist);
	void switchScreenTo(DISPLAY_TYPE screen);
	void createFeedback(std::string taskFeedback,std::string& feedback);
	void lastCmdCalledIs(std::string cmd);
	bool wasUndone();
	bool wasExecuted();
};
#endif