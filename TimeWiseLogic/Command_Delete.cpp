#pragma once
#include "Command_Delete.h"

Command_Delete::Command_Delete() {
	_type = DELETE;
}

Command_Delete::~Command_Delete(){
}

void Command_Delete::setDeletionIndex(unsigned int index){
	_deletionIndex = index;
}

void Command_Delete::setDeletionString(std::string deletionString){
	_deletionString = deletionString;
}

//only by index first
bool Command_Delete::execute(TaskList& taskList){
	Task temp = taskList.getTask(_deletionIndex);
	_beforeDelete.push(temp);
	if(taskList.deleteTask(_deletionIndex)) {
		return true;
	} else { 
		return false;
	}
}

bool Command_Delete::undo(TaskList& taskList){
	Task temp = _beforeDelete.top();
	taskList.addTask(temp);
	_beforeDelete.pop();
	return true;
}

