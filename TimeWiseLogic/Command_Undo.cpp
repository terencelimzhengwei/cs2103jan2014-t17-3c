#include "Command_Undo.h"


Command_Undo::Command_Undo(void)
{
	_type=UNDO;
}


Command_Undo::~Command_Undo(void)
{
}

bool Command_Undo::execute(TaskList& tasklist){
	return true;
}
bool Command_Undo::undo(TaskList& tasklist){
	return false;
}

