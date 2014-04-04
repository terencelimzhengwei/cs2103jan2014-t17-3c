#include "Command_Clear.h"

Command_Clear::Command_Clear(void){
	_type = CLEAR;
	_displayScreen = MAIN;
}

Command_Clear::Command_Clear(CLEAR_TYPE clearType){
	_type = CLEAR;
	_clearType = clearType;
	_displayScreen = MAIN;
}

Command_Clear::~Command_Clear(void){
	if(_lastCmdCalled == CMD_TYPE_STRING[8]){
		if(!_deletedUndoneTasks.empty()){
			for(unsigned int i = 0;i < _deletedUndoneTasks.size();i++){
				delete _deletedUndoneTasks[i];
				_deletedUndoneTasks[i] = NULL;
			}
			_deletedUndoneTasks.clear();
		}
	} else {
		_deletedUndoneTasks.clear();
	}
}

bool Command_Clear::execute(TaskList& tasklist, std::string& feedback){
	switch(_clearType){
	case ALL:
		clearAll(tasklist);
		feedback = CLEAR_ALL_SUCCESS;
		break;
	case UNCOMPLETED_TASKS:
		clearUncompletedTasks(tasklist);
		feedback = CLEAR_UNCOMPLETED_SUCCESS;
		break;
	case COMPLETED_TASKS:
		clearCompletedTasks(tasklist);
		feedback = CLEAR_COMPLETED_SUCCESS;
		break;
	case SCREEN:
		clearScreen(tasklist,feedback);
		break;
	default:
		_lastCmdCalled = CMD_TYPE_STRING[12];
		return false;
	}

	_lastCmdCalled = CMD_TYPE_STRING[12];
	return true;
}

bool Command_Clear::undo(TaskList& tasklist){
	switch(_clearType){
	case ALL:
		undoAll(tasklist);
		break;
	case UNCOMPLETED_TASKS:
		undoUncompletedTasks(tasklist);
		break;
	case COMPLETED_TASKS:
		undoCompletedTasks(tasklist);
		break;
	case SCREEN:
		if(_displayScreen == COMPLETE){
			undoCompletedTasks(tasklist);
		} else {
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
	if(_lastCmdCalled != CMD_TYPE_STRING[8]){
		for(int i = 0; i < tasklist.doneSize(); i++){
			_deletedDoneTasks.push_back(tasklist.getCompletedTask(i));
		} 
	}
	tasklist.clearCompletedTasks();
}

void Command_Clear::clearUncompletedTasks(TaskList& tasklist){
	if(_lastCmdCalled!="undo"){
		for(int i = 0; i<tasklist.undoneSize(); i++){
			_deletedUndoneTasks.push_back(tasklist.getTask(i));
		}
		if(_displayScreen == SEARCHED){
			saveSearchedTasks(tasklist);
		}else if(_displayScreen == FILTERED){
			saveFilteredTasks(tasklist);
		}
	}
	tasklist.clearTask();
}

void Command_Clear::clearAll(TaskList& tasklist){
	clearCompletedTasks(tasklist);
	clearUncompletedTasks(tasklist);
	tasklist.clearSearchedTasks();
	tasklist.clearFilteredTasks();
}

void Command_Clear::undoCompletedTasks(TaskList& tasklist){
	for(unsigned int i = 0; i<_deletedDoneTasks.size(); i++){
		tasklist.addTaskToDoneList(*_deletedDoneTasks[i]);
	}
}

void Command_Clear::undoUncompletedTasks(TaskList& tasklist){
	for(unsigned int i=0;i<_deletedUndoneTasks.size();i++){
		tasklist.addTask(*_deletedUndoneTasks[i]);
	}
	if(_displayScreen == SEARCHED){
		for(unsigned int i=0;i<_deletedSearchedTasks.size();i++){
			tasklist.addTask(*_deletedSearchedTasks[i]);
		}
		repopulateSearchList(tasklist);
	}else if(_displayScreen ==  FILTERED){
		for(unsigned int i = 0; i<_deletedFilteredTasks.size(); i++){
			tasklist.addTask(*_deletedFilteredTasks[i]);
		}
		repopulateFilterList(tasklist);
	}
}

void Command_Clear::undoAll(TaskList& tasklist){
	undoUncompletedTasks(tasklist);
	undoCompletedTasks(tasklist);
	if(_displayScreen == SEARCHED){
		repopulateSearchList(tasklist);
	}else if(_displayScreen == FILTERED){
		repopulateFilterList(tasklist);
	}
}

void Command_Clear::clearScreen(TaskList& tasklist,std::string& feedback) {
	if(_displayScreen == SEARCHED){
		if(_lastCmdCalled != CMD_TYPE_STRING[8]){
			saveSearchedTasks(tasklist);
		}
		tasklist.deleteSearchedTasks(); 
		feedback = CLEAR_SEARCHED_SUCCESS;
	} else if(_displayScreen == COMPLETE){
		clearCompletedTasks(tasklist);
		feedback = CLEAR_COMPLETED_SUCCESS;
	}else if(_displayScreen == MAIN){
		clearUncompletedTasks(tasklist);
		feedback = CLEAR_UNCOMPLETED_SUCCESS;
	}else if(_displayScreen == FILTERED){
		if(_lastCmdCalled != CMD_TYPE_STRING[8]){
			saveFilteredTasks(tasklist);
		}
		tasklist.deleteFilteredTasks();
		feedback = CLEAR_FILTERED_SUCCESS;
	}
	return;
}

void Command_Clear::setDisplayScreen(DISPLAY_TYPE displayType){
	_displayScreen = displayType;
}

void Command_Clear::saveSearchedTasks(TaskList &tasklist) {
	std::vector<Task*> searchedTask=tasklist.getSearchResults();
	for(unsigned int i=0;i<searchedTask.size();i++){
		_deletedSearchedTasks.push_back(searchedTask[i]);
	}
}

void Command_Clear::saveFilteredTasks(TaskList &tasklist) {
	std::vector<Task*> filteredTask=tasklist.getFilterResults();
	for(unsigned int i = 0;i<filteredTask.size();i++){
		_deletedFilteredTasks.push_back(filteredTask[i]);
	}
}

void Command_Clear::repopulateSearchList(TaskList &tasklist){
	tasklist.clearSearchedTasks();
	for(unsigned int i = 0; i < _deletedSearchedTasks.size(); i++){
		tasklist.addTaskToSearchedList(*_deletedSearchedTasks[i]);
	}
}

void Command_Clear::repopulateFilterList(TaskList &tasklist){
	tasklist.clearFilteredTasks();
	for(unsigned int i = 0; i < _deletedFilteredTasks.size(); i++){
		tasklist.addTaskToFilteredList(*_deletedFilteredTasks[i]);
	}
}
