//@author A0097277M
#ifndef COMMAND_SEARCH_H
#define COMMAND_SEARCH_H

#pragma once
#include "command.h"
//********************************************************************************
// This class takes in a keyword and searches for the keyword in tasklist and
// populating the searchlist in tasklist.
//********************************************************************************
class Command_Search :public Command{
public:
	Command_Search(void);
	~Command_Search(void);

	void setKeyword(std::string);
	void setPreviousScreen(DISPLAY_TYPE*);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&, std::string&);

private:
	void switchScreenTo(DISPLAY_TYPE screen);

	//Attributes
	std::string _keyword;

	DISPLAY_TYPE _previousScreen;
	DISPLAY_TYPE* _currentScreen;
};
#endif

