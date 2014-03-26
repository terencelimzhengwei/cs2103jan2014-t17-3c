#pragma once
#include "Command_Edit.h"


Command_Edit::Command_Edit() {
	_type = EDIT;
}
Command_Edit::~Command_Edit(){
}

void Command_Edit::setUserInput(std::string* input){
	_userInput=input;
}

void Command_Edit::setEditIndex(int index){
	_index=index;
}

bool Command_Edit::execute(TaskList& tasklist){
	Task* task;
	switch(_screen){
	case MAIN:
		task = tasklist.getTask(_index);
		break;
	case SEARCHED:
		task = tasklist.getSearchedTask(_index);
		break;
	default:
		throw UnableToEditCompletedTasks() ;
		
	}
	tasklist.setEditStatus(true);
	task->setEditStatus(true);
	*_userInput=task->toString();
}

bool Command_Edit::undo(TaskList& tasklist){
	return false;
}

void Command_Edit::setDisplayScreen(DISPLAY_TYPE type){
	_screen=type;
}




