#pragma once
#include "Command_Delete.h"

//@author A0097277M
Command_Delete::Command_Delete() {
        _type = DELETE;
        _deletionString = DEFAULT_EMPTY;
        //The default index is set to -1 when a new Command_Delete is dynamically created
        //so that it will not clash with any other task index
}

Command_Delete::~Command_Delete(){
	if(wasExecuted()){
		permanantlyDeleteTask();
	}else{
		_deletedTasks.clear();
	}
}

bool Command_Delete::execute(TaskList& taskList, std::string& feedback){

	if(wasUndone()){
		redo(taskList);
		lastCmdCalledIs(EXECUTE);
		createFeedback(DELETE_SUCCESS,feedback);
		return true;
	}else{
		backUpTasks(taskList);
		deleteTasks(taskList);
		lastCmdCalledIs(EXECUTE);
		createFeedback(DELETE_SUCCESS,feedback);
		return true;
	}
}

bool Command_Delete::undo(TaskList& taskList, std::string& feedback){
	switch(_displayType){
	case MAIN:
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTask(*_deletedTasks[i]);
		}
		break;
	case COMPLETE:
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTaskToDoneList(*_deletedTasks[i]);
		}
		break;
	case SEARCHED:
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTask(*_deletedTasks[i]);
			taskList.addTaskToSearchedList(*_deletedTasks[i]);
		}
		break;
	
	case FILTERED:
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTask(*_deletedTasks[i]);
			taskList.addTaskToFilteredList(*_deletedTasks[i]);
		}
		break;		
	default:
		break;
	}
	lastCmdCalledIs(CMD_TYPE_STRING[UNDO]);
	createFeedback(UNDO_DELETE_SUCCESS,feedback);
	return true;
}

void Command_Delete::setDisplayScreen(DISPLAY_TYPE display){
        _displayType = display;
}

void Command_Delete::addDeletionIndex(int index){
	_deletedTaskIndex.push_back(index);
}

void Command_Delete::lastCmdCalledIs(std::string cmd){
	_lastCmdCalled=cmd;
}

bool Command_Delete::wasUndone(){
	if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
		return true;
	}
	return false;
}

bool Command_Delete::wasExecuted(){
	if(_lastCmdCalled==EXECUTE){
		return true;
	}
	return false;
}

void Command_Delete::permanantlyDeleteTask(){
	for(unsigned int i=0;i<_deletedTasks.size();i++){
		delete _deletedTasks[i];
		_deletedTasks[i]=NULL;
	}
}

void Command_Delete::redo(TaskList& taskList){
	deleteTasks(taskList);
	lastCmdCalledIs(EXECUTE);
}

void Command_Delete::deleteTasks(TaskList& taskList){
	switch(_displayType){
	case MAIN:
		deleteMainTasks(taskList);
		break;
	case COMPLETE:
		deleteCompletedTasks(taskList);
		break;
	case SEARCHED:
		deleteSearchedTasks(taskList);
		break;
	case FILTERED:
		deleteFilterTasks(taskList);
		break;
	default:
		break;
	}

}

void Command_Delete::createFeedback(std::string taskFeedback,std::string& feedback){
	feedback=taskFeedback;
}

void Command_Delete::backUpTasks(TaskList &taskList){
	switch(_displayType){
	case MAIN:
		backUpMainTasks(taskList);
		break;
	case COMPLETE:
		backUpCompletedTasks(taskList);
		break;
	case SEARCHED:
		backUpSearchedTasks(taskList);
		break;
	case FILTERED:
		backUpFilteredTasks(taskList);
		break;
	default:
		break;
	}
}

void Command_Delete::backUpMainTasks(TaskList &taskList){
	for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
		if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
			_deletedTasks.push_back(taskList.getTask(_deletedTaskIndex[i]));
		}
	}
}

void Command_Delete::backUpCompletedTasks(TaskList &taskList){
	for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
		if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
			_deletedTasks.push_back(taskList.getCompletedTask(_deletedTaskIndex[i]));
		}
	}
}

void Command_Delete::backUpSearchedTasks(TaskList &taskList){
	for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
		if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
			_deletedTasks.push_back(taskList.getSearchedTask(_deletedTaskIndex[i]));
		}
	}
}

void Command_Delete::deleteMainTasks(TaskList& taskList){
	for(unsigned int i=0;i<_deletedTasks.size();i++){
		unsigned int index = taskList.getTaskIndex(_deletedTasks[i]);
		taskList.deleteTaskFromUncompletedList(index);
	}
}
void Command_Delete::deleteCompletedTasks(TaskList& taskList){
	for(unsigned int i=0;i<_deletedTasks.size();i++){
		unsigned int index = taskList.getTaskIndexInCompletedList(_deletedTasks[i]);
		taskList.deleteTaskFromCompletedList(index);
	}
}
void Command_Delete::deleteSearchedTasks(TaskList& taskList){
	for(unsigned int i=0;i<_deletedTasks.size();i++){
		unsigned int index = taskList.getTaskIndexInSearchedList(_deletedTasks[i]);
		taskList.deleteTaskFromSearchList(index);
	}
}
void Command_Delete::deleteFilterTasks(TaskList& taskList){
	for(unsigned int i=0;i<_deletedTasks.size();i++){
		unsigned int index = taskList.getTaskIndexInFilteredList(_deletedTasks[i]);
		taskList.deleteTaskFromFilterList(index);
	}
}

void Command_Delete::backUpFilteredTasks(TaskList &taskList){
	for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
		if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
			_deletedTasks.push_back(taskList.getFilteredTask(_deletedTaskIndex[i]));
		}
	}
}
