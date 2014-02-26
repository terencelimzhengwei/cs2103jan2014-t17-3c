#include "Command.h"


Command::Command(void){
}


Command::~Command(void){
}

std::string Command::getDescription() {
	return _description;
}

CMD_TYPE Command::getType() {
	return _type;
}
void Command::setType(CMD_TYPE type)
{
	_type=type;
}

void Command::setDescription(std::string desc)
{
	_description=desc;
}
