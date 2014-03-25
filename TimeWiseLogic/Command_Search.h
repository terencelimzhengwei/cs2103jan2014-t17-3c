#pragma once
#include "command.h"
class Command_Search :public Command
{
public:
	Command_Search(void);
	~Command_Search(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setKeyword(std::string keyword);
	void setPreviousScreen(DISPLAY_TYPE* screen);

private:
	std::string _keyword;

	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;

};

