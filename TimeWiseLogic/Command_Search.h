#pragma once
#include "command.h"

class Command_Search :public Command
{
public:
	Command_Search(void);
	~Command_Search(void);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&);
	void setKeyword(std::string);
	void setPreviousScreen(DISPLAY_TYPE*);

private:
	std::string _keyword;

	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;

};

