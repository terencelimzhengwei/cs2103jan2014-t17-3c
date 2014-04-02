#pragma once
#include "command.h"
class Command_Display :public Command{
public:
	Command_Display(void);
	~Command_Display(void);

	void setCurrentScreen(DISPLAY_TYPE* screen);
	void setNextScreen(DISPLAY_TYPE screen);
	bool execute(TaskList&, std::string&);
	bool undo(TaskList&);
private:
	DISPLAY_TYPE* _currentScreen;
	DISPLAY_TYPE _nextScreen;
};

