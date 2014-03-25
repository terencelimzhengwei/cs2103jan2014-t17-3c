#include "Command_Display.h"


Command_Display::Command_Display(void){
	_type=DISPLAY;
}


Command_Display::~Command_Display(void)
{
}

void Command_Display::setPreviousScreen(DISPLAY_TYPE* screen){
	_currentScreen=screen;
	_previousScreen=*screen;
}

void Command_Display::setNextScreen(DISPLAY_TYPE screen){
	_nextScreen=screen;
}

bool Command_Display::execute(TaskList&){
	*_currentScreen=_nextScreen;
	return true;
}

bool Command_Display::undo(TaskList&){
	*_currentScreen=_previousScreen;
	return true;
}