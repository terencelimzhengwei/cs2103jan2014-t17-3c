#include "Command_Done.h"


Command_Done::Command_Done(void){
	_type=DONE;
	_taskIndex=DEFAULT_INDEX;
	_task=NULL;
}


Command_Done::~Command_Done(void){
}

void Command_Done::setCompletedIndex(int index){
	_taskIndex=index;
}

bool Command_Done::execute(TaskList& tasklist){
	switch(_displayType){
	case MAIN:
		_task=tasklist.setTaskAsDone(_taskIndex);
		return true;
	case SEARCHED:
		_task=tasklist.setSearchedTaskAsDone(_taskIndex);
		return true;
	default:
		throw UnableTosetAsDone();
		return false;
	}
}

bool Command_Done::undo(TaskList& tasklist){
	unsigned int index = tasklist.getTaskIndexInCompletedList(_task);
	tasklist.setTaskAsUndone(index);
	tasklist.addTaskToSearchedList(*_task);
	return true;
}

void Command_Done::setDisplayScreen(DISPLAY_TYPE screen){
	_displayType=screen;
}
