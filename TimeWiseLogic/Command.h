#pragma once

#include "Constants.h"
#include <string>

class Command
{
public:
	Command(void);
	~Command(void);
	void setType(CMD_TYPE type);
	void setDescription(std::string desc);
private:
	CMD_TYPE _type;
	std::string _description;
};

