#ifndef COMMAND_ADD_H
#define COMMAND_ADD_H

#pragma once
#include "Command.h"

//************************************************************
// This class is responsible getting the attribute to be added
// to a task. It will set the attributes to the task before
// adding it to the tasklist. By default task will be set as
// floating task with no date and time parameters.
//************************************************************
// @author A0097277M
class Command_Add: public Command {
public:
	Command_Add();
	~Command_Add(void);

	//Set attributes to be included into the new task
	void setDescription(std::string);
	void setCategory(std::string);
	void setEndDate(Date&);
	void setStartDate(Date&);
	void setStartTime(ClockTime&);
	void setEndTime(ClockTime&);
	void setPreviousScreen(DISPLAY_TYPE*);

	//adds the task into the tasklist and returns the feedback
	virtual bool execute(TaskList&,std::string&);

	//Undo the task by deleting the task
	virtual bool undo(TaskList&, std::string&);

private:
	//These are the attributes for Command_Add
	//These 2 strings hold the task description and category of the task to be added
	std::string _taskDescription;
	std::string _category;
	//These 4 variables hold the time and date values for the task. If no date or time, these values will be null
	Date* _startDate;
	Date* _endDate;
	ClockTime* _startTime;
	ClockTime* _endTime;
	//This variable pointer points to the task to be added
	Task* _addedTask;
	//currentScreen holds the pointer to the actual screen the UI is displaying
	//previous screen holds the screen that user was on before adding task
	//These 2 variables are mainly used in undo and redo to ensure correct changing of screens
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _previousScreen;
	
	//lastCmdCalled is used to track whether undo or redo was called to execute the correct commands;
	std::string _lastCmdCalled;


//---Helper Functions-----------------------------------------------------------------
	//For Initialization
	void initDefaultValues();
	//For Destruction
	void resetEndDate();
	void resetStartDate();
	void resetEndTime();
	void resetTask();
	void resetDateAndTime() ;
	void resetStartTime();
	//Checking for Presence of Time and Date
	bool hasStartTime();
	bool hasStartDate();
	bool hasEndDate();
	bool hasEndTime();
	//Checking for which was the last executed command
	bool wasUndone();
	bool wasExecuted();
	//Creation of feedback
	void createFeedback(TaskList& taskList,std::string& feedback);
	void createFeedback(std::string taskFeedback,std::string& feedback);
	//Adding and Deletion of tasks
	void redo(TaskList& tasklist);
	void createTask(TaskList& tasklist);
	void removeAddedTask(TaskList& tasklist);
	//Others
	bool isClash(TaskList& tasklist);
	void switchScreenTo(DISPLAY_TYPE screen);
	void lastCmdCalledIs(std::string cmd);
	void setIndexToBoldInGUI(TaskList& tasklist);
};
#endif