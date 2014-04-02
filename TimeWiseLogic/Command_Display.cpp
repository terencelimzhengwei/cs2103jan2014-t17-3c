#include "Command_Display.h"


Command_Display::Command_Display(void){
	_type=DISPLAY;
}


Command_Display::~Command_Display(void)
{
}

void Command_Display::setCurrentScreen(DISPLAY_TYPE* screen){
	_currentScreen=screen;
}

void Command_Display::setNextScreen(DISPLAY_TYPE screen){
	_nextScreen=screen;
}

bool Command_Display::execute(TaskList&, std::string&){
	*_currentScreen=_nextScreen;
	return true;
}

bool Command_Display::undo(TaskList&){
	return false;
}