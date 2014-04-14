#include "Command_Undo.h"


Command_Undo::Command_Undo(void){
	_type = UNDO;
}

Command_Undo::~Command_Undo(void){
}

bool Command_Undo::execute(TaskList& tasklist, std::string& feedback){
	feedback = SUCCESS;
	return true;
}

bool Command_Undo::undo(TaskList& tasklist, std::string&){
	return false;
}

