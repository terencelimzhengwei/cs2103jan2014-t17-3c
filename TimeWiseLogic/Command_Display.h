#ifndef COMMAND_DISPLAY_H
#define COMMAND_DISPLAY_H

#pragma once

#include "command.h"
//************************************************************
// This class is responsible for setting the display screen:
// MAIN,SEARCHED,COMPLETE,FILTERED
// 1. MAIN SCREEN: displays all uncompleted tasks.
// 2. SEARCHED SCREEN: displays all searched tasks.
// 3. COMPLETE SCREEN: displays all completed tasks.
// 4. FILTERED SCREEN: displays all filtered tasks.
//************************************************************
// @author A0097277M
class Command_Display :public Command{
public:
	Command_Display(void);
	~Command_Display(void);
	
	void setCurrentScreen(DISPLAY_TYPE* screen);
	void setNextScreen(DISPLAY_TYPE screen);

	bool execute(TaskList&, std::string&);
	bool undo(TaskList&,std::string&);

private:
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _nextScreen;
};
#endif
