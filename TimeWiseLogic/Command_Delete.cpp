#pragma once
#include "Command_Delete.h"

Command_Delete::Command_Delete() {
	_type = DELETE;
	_deletionString="";
	_deletionIndex=DEFAULT_INDEX;
	_taskDeleted=NULL;
}

Command_Delete::~Command_Delete(){
	if(_lastCmdCalled=="execute"){
		delete _taskDeleted;
		_taskDeleted=NULL;
	}else{
		_taskDeleted=NULL;
	}
}

void Command_Delete::setDeletionIndex(int index){
	_deletionIndex = index;
}

void Command_Delete::setDeletionString(std::string deletionString){
	_deletionString = deletionString;
}

//only by index first
bool Command_Delete::execute(TaskList& taskList){
	switch(_displayType){
	case MAIN:
		if(_deletionIndex!=DEFAULT_INDEX ){
			_taskDeleted=taskList.getTask(_deletionIndex);
			taskList.deleteTask(_deletionIndex);
			_lastCmdCalled="execute";
			return true;
		}/*else if(_deletionString!=DEFAULT_EMPTY){
			//search delete
			return true;
		}*/
	case COMPLETE:
		if(_deletionIndex!=DEFAULT_INDEX){
			_taskDeleted=taskList.getCompletedTask(_deletionIndex);
			taskList.deleteTaskFromCompletedList(_deletionIndex);
			_lastCmdCalled="execute";
			return true;
		}else if(_deletionString!=DEFAULT_EMPTY){
			//search delete
			return true;
		}
	case SEARCHED:
		if(_deletionIndex!=DEFAULT_INDEX){
			_taskDeleted=taskList.getSearchedTask(_deletionIndex);
			taskList.deleteTaskFromSearchList(_deletionIndex);
			_lastCmdCalled="execute";
			return true;
		}else if(_deletionString!=DEFAULT_EMPTY){
			//search delete
			return true;
		}
	}
	return false;
}

bool Command_Delete::undo(TaskList& taskList){
	switch(_displayType){
	case MAIN:
		taskList.addTask(*_taskDeleted);
		_lastCmdCalled="undo";
		break;
	case COMPLETE:
		taskList.addTaskToDoneList(*_taskDeleted);
		_lastCmdCalled="undo";
		break;
	case SEARCHED:
		taskList.addTask(*_taskDeleted);
		std::vector<Task*>& searchResults=taskList.getSearchResults();
		searchResults.push_back(_taskDeleted);
		_lastCmdCalled="undo";
		break;
	}
	return true;
}

void Command_Delete::setDisplayScreen(DISPLAY_TYPE display){
	_displayType=display;
}

