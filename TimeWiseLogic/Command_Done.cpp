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
	_task=tasklist.setTaskAsDone(_taskIndex);
	return true;
}

bool Command_Done::undo(TaskList& tasklist){
	unsigned int index = tasklist.getTaskIndexInCompletedList(_task);
	tasklist.setTaskAsUndone(index);
	return true;
}
