#pragma once
#include "command.h"
class Command_Filter :public Command
{
public:
	Command_Filter(void);
	~Command_Filter(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setCategory(std::string category);
	void setPriority(PRIORITY priority);
	void setDate(Date* date);
	void setPreviousScreen(DISPLAY_TYPE* screen);

private:
	FILTER_TYPE _filterType;
	std::string _category;
	PRIORITY _priority;
	Date* _date;
	
	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;

};

