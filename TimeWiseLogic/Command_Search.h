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

private:
	std::string _keyword;
};

