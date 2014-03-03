#pragma once
#include "Command.h"

class Command_Delete : public Command
{
public:
	Command_Delete();
	~Command_Delete(void);
	unsigned long long getIndex();
	std::string	getDescription();
};

