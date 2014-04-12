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
	void setDate(Date*);
	void setPreviousScreen(DISPLAY_TYPE*);
	void switchScreenTo(DISPLAY_TYPE screen);
private:
	FILTER_TYPE _filterType;
	std::string _category;
	Date* _date;
	
	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;

};

