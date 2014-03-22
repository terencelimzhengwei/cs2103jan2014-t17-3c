#include "Command_Undone.h"


Command_Undone::Command_Undone(void){
	_type=UNDONE;
	_taskIndex=DEFAULT_INDEX;
	_task=NULL;
}


Command_Undone::~Command_Undone(void){
	_task=NULL;
}

bool Command_Undone::execute(TaskList& tasklist){
	_task=tasklist.getTask(_taskIndex);
	_task->setStatusasUndone();
	return true;
}

bool Command_Undone::undo(TaskList& tasklist){
	unsigned int index = tasklist.getTaskIndex(_task);
	tasklist.getTask(index)->setStatusAsDone();
	return true;
}

void Command_Undone::setUncompletedIndex(unsigned int index){
	_taskIndex=index;
}
