#ifndef COMMAND_FILTER_H
#define COMMAND_FILTER_H

#pragma once

#include "command.h"
//********************************************************************************
// This class is responsible for filtering out tasks which are scheduled on the 
// same dates (due dates or end dates) or belong to the same category
//********************************************************************************
// @author A0097277M
class Command_Filter :public Command
{
public:
	Command_Filter(void);
	~Command_Filter(void);

	void setCategory(std::string);
	void setDate(Date*);
	void setPreviousScreen(DISPLAY_TYPE*);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);

private:
	FILTER_TYPE _filterType;
	std::string _category;
	Date* _date;
	
	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;

	void switchScreenTo(DISPLAY_TYPE screen);

};
#endif
