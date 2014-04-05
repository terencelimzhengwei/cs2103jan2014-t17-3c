#include "Command_Redo.h"


Command_Redo::Command_Redo(void)
{
	_type = REDO;
}


Command_Redo::~Command_Redo(void)
{
}

bool Command_Redo::execute(TaskList& tasklist, std::string& feedback){
	feedback = SUCCESS;
	return true;
}

bool Command_Redo::undo(TaskList& tasklist, std::string&){
	return false;
}

