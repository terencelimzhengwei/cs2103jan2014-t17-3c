#pragma once
#include "Command.h"

class Command_Display : public Command
{
public:
	Command_Display();
	~Command_Display(void);

	unsigned long long 	getIndex();
	void setIndex(unsigned long long);
};

