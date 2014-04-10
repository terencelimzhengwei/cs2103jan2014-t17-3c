#pragma once
#include "Command_Delete.h"

Command_Delete::Command_Delete() {
        _type = DELETE;
        _deletionString = DEFAULT_EMPTY;
        //The default index is set to -1 when a new Command_Delete is dynamically created
        //so that it will not clash with any other task index
        _deletionIndex = DEFAULT_INDEX;
}

Command_Delete::~Command_Delete(){
        if(_lastCmdCalled == EXECUTE){
                for(unsigned int i=0;i<_deletedTasks.size();i++){
					delete _deletedTasks[i];
					_deletedTasks[i]=NULL;
				}
        }else{
                _deletedTasks.clear();
        }
}

bool Command_Delete::execute(TaskList& taskList, std::string& feedback){
	switch(_displayType){
	case MAIN:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_deletedTaskIndex.size();i++){
				taskList.deleteTask(_deletedTaskIndex[i]);
			}
			_lastCmdCalled=EXECUTE;
			return true;
		}
		for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
			if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
				_deletedTasks.push_back(taskList.getTask(_deletedTaskIndex[i]));
				taskList.deleteTask(_deletedTaskIndex[i]);
				_lastCmdCalled = EXECUTE;
				feedback = DELETE_SUCCESS;
			}
		}
		return true;
	case COMPLETE:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_deletedTaskIndex.size();i++){
				taskList.deleteTaskFromCompletedList(_deletedTaskIndex[i]);
			}
			_lastCmdCalled=EXECUTE;
		}
		for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
			if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
				_deletedTasks.push_back(taskList.getCompletedTask(_deletedTaskIndex[i]));
				taskList.deleteTaskFromCompletedList(_deletedTaskIndex[i]);
				_lastCmdCalled = EXECUTE;
				feedback = DELETE_SUCCESS;
			}
		}
		return true;
	case SEARCHED:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_deletedTaskIndex.size();i++){
				taskList.deleteTaskFromSearchList(_deletedTaskIndex[i]);
			}
			_lastCmdCalled=EXECUTE;
		}
		for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
			if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
				_deletedTasks.push_back(taskList.getSearchedTask(_deletedTaskIndex[i]));
				taskList.deleteTaskFromSearchList(_deletedTaskIndex[i]);
				_lastCmdCalled = EXECUTE;
				feedback = DELETE_SUCCESS;
			}
		}
		return true;
	case FILTERED:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_deletedTaskIndex.size();i++){
				taskList.deleteTaskFromFilterList(_deletedTaskIndex[i]);
			}
			_lastCmdCalled=EXECUTE;
		}
		for(unsigned int i =0;i<_deletedTaskIndex.size();i++){
			if(_deletedTaskIndex[i] != DEFAULT_INDEX ){
				_deletedTasks.push_back(taskList.getFilteredTask(_deletionIndex));
				taskList.deleteTaskFromFilterList(_deletionIndex);
				_lastCmdCalled = EXECUTE;
				feedback = DELETE_SUCCESS;
			}
		}
		return true;
	}
	return false;
}

bool Command_Delete::undo(TaskList& taskList, std::string& feedback){
	int checkClash;
	switch(_displayType){
	case MAIN:
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTask(*_deletedTasks[i],checkClash);
		}
		_lastCmdCalled = CMD_TYPE_STRING[UNDO];
		feedback = UNDO_DELETE_SUCCESS;
		break;
	case COMPLETE:
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTaskToDoneList(*_deletedTasks[i]);
		}
		_lastCmdCalled = CMD_TYPE_STRING[UNDO];
		feedback = UNDO_DELETE_SUCCESS;
		break;
	case SEARCHED:{
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTask(*_deletedTasks[i],checkClash);
			taskList.addTaskToSearchedList(*_deletedTasks[i]);
		}
		_lastCmdCalled = CMD_TYPE_STRING[UNDO];
		feedback = UNDO_DELETE_SUCCESS;
		break;
				  }
	case FILTERED:{
		for(unsigned int i=0;i<_deletedTasks.size();i++){
			taskList.addTask(*_deletedTasks[i],checkClash);
			taskList.addTaskToFilteredList(*_deletedTasks[i]);
		}
		_lastCmdCalled = CMD_TYPE_STRING[UNDO];
		feedback = UNDO_DELETE_SUCCESS;
		break;
				  }
	}
	return true;
}

void Command_Delete::setDisplayScreen(DISPLAY_TYPE display){
        _displayType = display;
}

void Command_Delete::addDeletionIndex(int index){
	_deletedTaskIndex.push_back(index);
}
