#ifndef COMMAND_EDIT_H
#define COMMAND_EDIT_H

#pragma once
#include "command.h"
//********************************************************************************
// This class contains methods which are responsible for modifying fields of an
// individual task specified by its index on the display screen that the users are
// working with. Regardless of the display screen, it is always possible to edit a
// task.
//********************************************************************************
// @author A0097277M
class Command_Edit :public Command
{
public:
	Command_Edit(void);
	~Command_Edit(void);

	// setter methods for fields. They take in the new content for each field 
	// from the user and reset the task accordingly.
	void setIndex(int);
	void setDescription(std::string);
	void setCategory(std::string);
	void setEndDate(Date*);
	void setStartDate(Date*);
	void setStartTime(ClockTime*);
	void setEndTime(ClockTime*);
	void setDisplayScreen(DISPLAY_TYPE);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);

private:
	int _editIndex;
	std::string _editedDescription;
	std::string _editedCategory;
	Date* _editedEndDate;
	Date* _editedStartDate;
	ClockTime* _editedEndTime;
	ClockTime* _editedStartTime;

	std::string _originalDescription;
	std::string _originalCategory;
	Date* _originalEndDate;
	Date* _originalStartDate;
	ClockTime* _originalEndTime;
	ClockTime* _originalStartTime;

	Task* _editedTask;

	DISPLAY_TYPE _displayScreen;

	//For initialization
	void initialiseParameters();

	//For undoing of task
	void saveOriginalTaskDetails();
	void getOriginalTask(TaskList& tasklist);
	void revertParameters();
	
	//For execution of task
	void resetTimeAndDate();
	void editTaskWithNewParameters();

	//check for missing parameters
	bool noDateAndTime();
	bool noDate();
	bool noTime();
	bool emptyParameters();
	bool noCategory();
	bool noDescription();
	bool noEndTime();
	bool noStartTime();
	bool noStartDate();
	bool noEndDate();

	//Helper Functions
	void setIndexToBoldInGUI(TaskList& tasklist);
	void createFeedback(std::string taskFeedback,std::string& feedback);
};
#endif
