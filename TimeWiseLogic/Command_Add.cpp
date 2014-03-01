#include "Command_Add.h"


Command_Add::Command_Add(void){
}


Command_Add::~Command_Add(void){
}

std::string Command_Add::getDescription() {
	return _description;
}

CMD_TYPE Command_Add::getType() {
	return _type;
}
void Command_Add::setType(CMD_TYPE type)
{
	_type = type;
}

void Command_Add::setDescription(std::string desc)
{
	_description=desc;
}
