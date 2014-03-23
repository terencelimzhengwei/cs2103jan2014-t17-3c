#include "Command_Clear.h"

Command_Clear::Command_Clear(void){
	_type=CLEAR;
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
	for(int i=0;i<tasklist.undoneSize();i++){
		_deletedTasks.push_back(tasklist.getTask(i));
	}
	tasklist.clearTask();
	_lastCmdCalled="execute";
	return true;
}

bool Command_Clear::undo(TaskList& tasklist){
	if(tasklist.isEmpty()){
		for(int i=0;i<_deletedTasks.size();i++){
			tasklist.addTask(*_deletedTasks[i]);
		}
		_lastCmdCalled="undo";
		return true;
	}
	return false;
}
