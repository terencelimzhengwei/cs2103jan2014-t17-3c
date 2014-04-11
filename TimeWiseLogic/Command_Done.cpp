#include "Command_Done.h"


Command_Done::Command_Done(void){
	_type = DONE;
	_taskIndex = DEFAULT_INDEX;
	_task = NULL;
	_displayType = COMPLETE;
}


Command_Done::~Command_Done(void){
}

void Command_Done::setCompletedIndex(int index){
	_taskIndex = index;
}

bool Command_Done::execute(TaskList& tasklist, std::string& feedback){
	switch(_displayType){
	case MAIN:
		_task=tasklist.setTaskAsDone(_taskIndex);
		feedback = DONE_SUCCESS;
		_lastCmdCalled = EXECUTE;
		return true;
	case SEARCHED:
		_task=tasklist.setSearchedTaskAsDone(_taskIndex);
		feedback = DONE_SUCCESS;
		_lastCmdCalled = EXECUTE;
		return true;
	case FILTERED:
		_task=tasklist.setFilteredTaskAsDone(_taskIndex);
		feedback = DONE_SUCCESS;
		_lastCmdCalled = EXECUTE;
		return true;
	case COMPLETE:
		throw UnableTosetAsDone();
		return false;
	default:
		if(_lastCmdCalled == CMD_TYPE_STRING[UNDO]){
			_task = tasklist.setTaskAsDone(_taskIndex);
			_lastCmdCalled = EXECUTE;
			return true;
		}
		return false;
	}
}

bool Command_Done::undo(TaskList& tasklist, std::string& feedback){
	unsigned int index = tasklist.getTaskIndexInCompletedList(_task);
	tasklist.setTaskAsUndone(index);
	if(_displayType == SEARCHED){
		tasklist.addTaskToSearchedList(*_task);
	}else if(_displayType == FILTERED){
		tasklist.addTaskToFilteredList(*_task);
	}
        _lastCmdCalled = CMD_TYPE_STRING[8];
	feedback = UNDONE_SUCCESS;
	return true;
}

void Command_Done::setDisplayScreen(DISPLAY_TYPE screen){
	_displayType = screen;
}
