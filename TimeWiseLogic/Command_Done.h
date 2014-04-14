//@author A0097277M
#ifndef COMMAND_DONE_H
#define COMMAND_DONE_H
#pragma once

#include "command.h"
//********************************************************************************
// This class contains methods which are responsible for changing the status of
// an individual task from UNDONE to DONE.
// The individual task is specified by its index.
//********************************************************************************
class Command_Done : public Command{
public:
	Command_Done(void);
	~Command_Done(void);
	//Adds index of task to be done
	void addDoneIndex(int);
	//Sets screen so that Command will know which tasklist to done task
	void setPreviousScreen(DISPLAY_TYPE* screen);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);

private:

	void saveTasks(TaskList& taskList);
	void setTasksAsDone(TaskList& tasklist);
	void setDoneTasksAsUndone(TaskList& tasklist);

	bool checkDoneStatus();

	void switchScreenTo(DISPLAY_TYPE screen);
	void createFeedback(std::string taskFeedback,std::string& feedback);
	void lastCmdCalledIs(std::string cmd);
	bool wasUndone();
	bool wasExecuted();

	//Sets Index of Done Task to bold
	void setIndexToBoldInGUI(TaskList& tasklist);

	//Attributes
	std::vector<Task*> _doneTasks;
	std::vector<unsigned int> _doneTaskIndex;
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE  _previousScreen;
	std::string   _lastCmdCalled;
};
#endif
