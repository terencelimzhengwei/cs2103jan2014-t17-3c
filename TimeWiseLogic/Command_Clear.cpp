#include "Command_Clear.h"

Command_Clear::Command_Clear(void){
	_type=CLEAR;
}

Command_Clear::Command_Clear(CLEAR_TYPE clearType){
	_type=CLEAR;
	_clearType=clearType;
}

Command_Clear::~Command_Clear(void){
	if(_lastCmdCalled == "execute"){
		if(!_deletedTasks.empty()){
			for(int i=0;i<_deletedTasks.size();i++){
				delete _deletedTasks[i];
				_deletedTasks[i]=NULL;
			}
			_deletedTasks.clear();
		}
	}else{
		_deletedTasks.clear();
	}
}

bool Command_Clear::execute(TaskList& tasklist){
	if(!_deletedTasks.empty()){
		_deletedTasks.clear();
	}
	switch(_clearType){
	case ALL:
		clearAll(tasklist);
		break;
	case UNCOMPLETED_TASKS:
		clearUncompletedTasks(tasklist);
		break;
	case COMPLETED_TASKS:
		clearCompletedTasks(tasklist);
		break;
	case SCREEN:
		clearScreen(tasklist);
		break;
	default:
		_lastCmdCalled="execute";
		return false;
	}

	_lastCmdCalled="execute";

	return true;
}

bool Command_Clear::undo(TaskList& tasklist){
	switch(_clearType){
	case ALL:
		undoCompletedTasks(tasklist);
		undoUncompletedTasks(tasklist);
		break;
	case UNCOMPLETED_TASKS:
		undoUncompletedTasks(tasklist);
		break;
	case COMPLETED_TASKS:
		undoCompletedTasks(tasklist);
		break;
	case SCREEN:
		if(_displayType==COMPLETE){
			undoCompletedTasks(tasklist);
		}else{
			undoUncompletedTasks(tasklist);
		}
		break;
	default:
		return false;
	}
	_lastCmdCalled="undo";

	return true;
}

void Command_Clear::clearCompletedTasks(TaskList& tasklist){
	for(int i=0;i<tasklist.doneSize();i++){
		_deletedTasks.push_back(tasklist.getCompletedTask(i));
	}
	tasklist.clearCompletedTasks();
}

void Command_Clear::clearUncompletedTasks(TaskList& tasklist){
	for(int i=0;i<tasklist.undoneSize();i++){
		_deletedTasks.push_back(tasklist.getTask(i));
	}
	tasklist.clearTask();
}

void Command_Clear::clearAll(TaskList& tasklist){
	clearCompletedTasks(tasklist);
	clearUncompletedTasks(tasklist);
}

void Command_Clear::undoCompletedTasks(TaskList& tasklist){
	for(int i=0;i<_deletedTasks.size();i++){
		tasklist.addTaskToDoneList(*_deletedTasks[i]);
	}
}

void Command_Clear::undoUncompletedTasks(TaskList& tasklist){
	for(int i=0;i<_deletedTasks.size();i++){
		tasklist.addTask(*_deletedTasks[i]);
	}
}

void Command_Clear::undoAll(TaskList& tasklist){
	undoCompletedTasks(tasklist);
	undoUncompletedTasks(tasklist);
}

void Command_Clear::clearScreen(TaskList& tasklist){
	if(_displayType==SEARCHED){
		std::vector<Task*> searchedTask=tasklist.getSearchResults();
		for(int i=0;i<searchedTask.size();i++){
			_deletedTasks.push_back(searchedTask[i]);
		}
		tasklist.deleteSearchedTasks();
	}else if(_displayType==COMPLETE){
		clearCompletedTasks(tasklist);
	}else if(_displayType==MAIN){
		clearUncompletedTasks(tasklist);
	}
	return;
}

void Command_Clear::setDisplayScreen(DISPLAY_TYPE displayType){
	_displayType=displayType;
}
