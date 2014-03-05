#include "Command.h"

Command::Command(void){
	_type=UNDEFINED;
}

Command::~Command(void){
}

CMD_TYPE Command::getType(){
	return _type;
}