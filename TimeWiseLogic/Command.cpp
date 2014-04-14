#include "Command.h"

//@author A0097277M
Command::Command(void){
	_type=UNDEFINED;
}

Command::~Command(void){
}

CMD_TYPE Command::getType(){
	return _type;
}