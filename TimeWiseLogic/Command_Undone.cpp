#include "Command_Undone.h"


Command_Undone::Command_Undone(void){
	_type=UNDONE;
	_taskIndex=DEFAULT_INDEX;
	_task=NULL;
}


Command_Undone::~Command_Undone(void){
	_task=NULL;
}

bool Command_Undone::execute(TaskList& tasklist, std::string& feedback){
	if(_displayType== COMPLETE){
		Task* task = tasklist.getCompletedTask(_taskIndex);
		_task=task;
		tasklist.setTaskAsUndone(_taskIndex);
		feedback = "Task: '" + _task->toString() + "' has been marked as uncompleted";
		return true;
	}else{
		throw UnableToUndoneUncompletedTasks();
		return false;
	}
}

bool Command_Undone::undo(TaskList& tasklist){
	int index = tasklist.getTaskIndex(_task);
	tasklist.setTaskAsDone(index);
	return true;
}

void Command_Undone::setUncompletedIndex(int index){
	_taskIndex=index;
}

void Command_Undone::setDisplayScreen(DISPLAY_TYPE screen){
	_displayType=screen;
}
