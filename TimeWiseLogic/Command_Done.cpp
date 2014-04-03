#include "Command_Done.h"


Command_Done::Command_Done(void){
	_type=DONE;
	_taskIndex=DEFAULT_INDEX;
	_task=NULL;
	_displayType = COMPLETE;
}


Command_Done::~Command_Done(void){
}

void Command_Done::setCompletedIndex(int index){
	_taskIndex=index;
}

bool Command_Done::execute(TaskList& tasklist, std::string& feedback){
	switch(_displayType){
	case MAIN:
		_task=tasklist.setTaskAsDone(_taskIndex);
		_lastCmdCalled="execute";
		return true;
	case SEARCHED:
		_task=tasklist.setSearchedTaskAsDone(_taskIndex);
		_lastCmdCalled="execute";
		return true;
	case COMPLETE:
		throw UnableTosetAsDone();
		return false;
	default:
		if(_lastCmdCalled=="undo"){
			_task=tasklist.setTaskAsDone(_taskIndex);
			_lastCmdCalled="execute";
			break;
		}
		return false;
	}
	feedback = "Task: '" + _task->toString() + "' has been marked as completed";
}

bool Command_Done::undo(TaskList& tasklist){
	unsigned int index = tasklist.getTaskIndexInCompletedList(_task);
	tasklist.setTaskAsUndone(index);
	tasklist.addTaskToSearchedList(*_task);
	_lastCmdCalled="undo";
	return true;
}

void Command_Done::setDisplayScreen(DISPLAY_TYPE screen){
	_displayType = screen;
}
