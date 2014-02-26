#pragma once
#ifndef _Command_H
#define _Command_H

#include "Constants.h"
#include <string>

class Command
{
public:
	Command(void);
	~Command(void);
	std::string getDescription();
	CMD_TYPE getType();
	void setType(CMD_TYPE type);
	void setDescription(std::string desc);
private:
	CMD_TYPE _type;
	std::string _description;
};
#endif
