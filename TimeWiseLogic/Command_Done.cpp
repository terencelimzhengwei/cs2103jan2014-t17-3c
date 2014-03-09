#include "Command_Done.h"


Command_Done::Command_Done(void){
	_type=DONE;
	_taskIndex=DEFAULT_INDEX;
	_task=NULL;
}


Command_Done::~Command_Done(void){
}

void Command_Done::setCompletedIndex(unsigned int index){
	_taskIndex=index;
}

bool Command_Done::execute(TaskList& tasklist){
	_task=tasklist.getTask(_taskIndex);
	_task->setStatusAsDone();
	return true;
}

bool Command_Done::undo(TaskList& tasklist){
	unsigned int index = tasklist.getTaskIndex(_task);
	tasklist.getTask(index)->setStatusasUndone();
	return true;
}
