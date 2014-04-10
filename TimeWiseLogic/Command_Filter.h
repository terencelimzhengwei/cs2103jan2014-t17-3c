#pragma once
#include "command.h"
//********************************************************************************
// This class is responsible for filtering out tasks which are scheduled on the 
// same dates (due dates or end dates) or belong to the same category
//********************************************************************************
class Command_Filter :public Command
{
public:
	Command_Filter(void);
	~Command_Filter(void);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);
	void setCategory(std::string);
	void setPriority(PRIORITY);
	void setDate(Date*);
	void setPreviousScreen(DISPLAY_TYPE*);

private:
	FILTER_TYPE _filterType;
	std::string _category;
	PRIORITY _priority;
	Date* _date;
	
	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;

};

