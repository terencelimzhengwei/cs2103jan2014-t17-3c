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

void Command_Delete::setDeletionIndex(unsigned int index){
	_deletionIndex = index;
}

void Command_Delete::setDeletionString(std::string deletionString){
	_deletionString = deletionString;
}

//only by index first
bool Command_Delete::execute(TaskList& taskList){
	if(_deletionIndex!=DEFAULT_INDEX){
		_taskDeleted=taskList.getTask(_deletionIndex);
		taskList.deleteTask(_deletionIndex);
		_lastCmdCalled="execute";
		return true;
	}else if(_deletionString!=DEFAULT_EMPTY){
		//search delete
		return true;
	}
	return false;
}

bool Command_Delete::undo(TaskList& taskList){
	taskList.addTask(*_taskDeleted);
	_lastCmdCalled="undo";
	return true;
}

