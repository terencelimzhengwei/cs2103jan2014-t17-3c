#include "Command.h"


Command::Command(void){
}


Command::~Command(void){
}

void Command::setType(CMD_TYPE type)
{
	_type=type;
}

void Command::setDescription(std::string desc)
{
	_description=desc;
}
