#pragma once
#include "Command.h"
#include <stack>


class Command_Edit : public Command {
public:
	Command_Edit();
	~Command_Edit(void);

	//setter for fields
	void setUserInput(std::string* input);
	void setEditIndex(int index);
	void setDisplayScreen(DISPLAY_TYPE type);
	virtual bool execute(TaskList& tasklist);
	virtual bool undo(TaskList& taskList);

private:
	std::string* _userInput;
	DISPLAY_TYPE _screen;
	int _index;
};

