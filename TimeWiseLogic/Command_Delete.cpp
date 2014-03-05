#pragma once
#include "Command_Delete.h"

Command_Delete::Command_Delete() {
	_type=DELETE;
}

Command_Delete::~Command_Delete(){
}

void Command_Delete::setDeletionIndex(int index){
	_deletionIndex=index;
}

void Command_Delete::setDeletionString(std::string deletionString){
	_deletionString=deletionString;
}

bool Command_Delete::execute(TaskList& tasklist){
	return true;
}

bool Command_Delete::undo(TaskList& taskList){
	return true;
}

