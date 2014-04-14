//@author A0097277M
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
	if(wasExecuted()){
		permanantlyDeleteTasks();
		_deletedUndoneTasks.clear();
	}else{
		_deletedUndoneTasks.clear();
	}
}

bool Command_Clear::execute(TaskList& tasklist, std::string& feedback){
	switch(_clearType){
	case ALL:{
		clearAll(tasklist);
		createFeedback(CLEAR_ALL_SUCCESS,feedback);
		break;
	}
	case UNCOMPLETED_TASKS:{
		clearUncompletedTasks(tasklist);
		createFeedback(CLEAR_UNCOMPLETED_SUCCESS,feedback);
		break;
	}
	case COMPLETED_TASKS:{
		clearCompletedTasks(tasklist);
		createFeedback(CLEAR_COMPLETED_SUCCESS,feedback);
		break;
	}
	case SCREEN:{
		clearScreen(tasklist,feedback);
		break;
	}
	default:
		return false;
	}
	lastCmdCalledIs(EXECUTE);
	return true;
}

bool Command_Clear::undo(TaskList& tasklist, std::string& feedback){
	switch(_clearType){
	case ALL:{
		undoAll(tasklist,feedback);
		break;
	}
	case UNCOMPLETED_TASKS:{
		undoUncompletedTasks(tasklist, feedback);
		break;
	}
	case COMPLETED_TASKS:{
		undoCompletedTasks(tasklist,feedback);
		break;
	}
	case SCREEN: {
		undoScreenTasks(tasklist,feedback);
		break;
	}
	default:
		return false;
	}
	lastCmdCalledIs(CMD_TYPE_STRING[UNDO]);
	return true;
}

void Command_Clear::clearCompletedTasks(TaskList& tasklist){
	if(!wasUndone()){
		for(unsigned int i = 0; i < tasklist.doneSize(); i++){
			_deletedDoneTasks.push_back(tasklist.getCompletedTask(i));
		} 
	}
	tasklist.clearCompletedTasks();
}

void Command_Clear::clearUncompletedTasks(TaskList& tasklist){
	if(!wasUndone()){
		for(unsigned int i = 0; i <tasklist.undoneSize(); i++){
			_deletedUndoneTasks.push_back(tasklist.getTask(i));
		}
	}
	tasklist.clearTask();
}

void Command_Clear::clearAll(TaskList& tasklist){
	clearCompletedTasks(tasklist);
	clearUncompletedTasks(tasklist);
	tasklist.resetSearchedTasks();
	tasklist.resetFilteredTasks();
}

void Command_Clear::undoCompletedTasks(TaskList& tasklist, std::string& feedback){
	for(unsigned int i = 0; i <_deletedDoneTasks.size(); i++){
		tasklist.addTaskToDoneList(*_deletedDoneTasks[i]);
	}
	createFeedback(UNDO_CLEAR_COMPLETED_SUCCESS,feedback);
}

void Command_Clear::undoUncompletedTasks(TaskList& tasklist, std::string& feedback){
	for(unsigned int i = 0;i < _deletedUndoneTasks.size();i++){
		tasklist.addTask(*_deletedUndoneTasks[i]);
		createFeedback(UNDO_CLEAR_UNCOMPLETED_SUCCESS,feedback);
	}
}

void Command_Clear::undoAll(TaskList& tasklist, std::string& feedback){
	undoUncompletedTasks(tasklist,feedback);
	undoCompletedTasks(tasklist,feedback);
	if(_displayScreen == SEARCHED){
		repopulateSearchList(tasklist);
	}else if(_displayScreen == FILTERED){
		repopulateFilterList(tasklist);
	}
	createFeedback(UNDO_CLEAR_ALL_SUCCESS,feedback);
}

void Command_Clear::clearScreen(TaskList& tasklist,std::string& feedback) {
	if(_displayScreen == SEARCHED){
		if(!wasUndone()){
			saveSearchedTasks(tasklist);
		}
		tasklist.clearSearchedTasks(); 
		createFeedback(CLEAR_SEARCHED_SUCCESS,feedback);
	} else if(_displayScreen == COMPLETE){
		clearCompletedTasks(tasklist);
		createFeedback(CLEAR_COMPLETED_SUCCESS,feedback);
	}else if(_displayScreen == MAIN){
		clearUncompletedTasks(tasklist);
		createFeedback(CLEAR_UNCOMPLETED_SUCCESS,feedback);
	}else if(_displayScreen == FILTERED){
		if(_lastCmdCalled != CMD_TYPE_STRING[UNDO]){
			saveFilteredTasks(tasklist);
		}
		tasklist.clearFilteredTasks();
		createFeedback(CLEAR_FILTERED_SUCCESS,feedback);
	}
	return;
}

void Command_Clear::setDisplayScreen(DISPLAY_TYPE displayType){
	_displayScreen = displayType;
}

void Command_Clear::saveSearchedTasks(TaskList &tasklist) {
	std::vector<Task*> searchedTask=tasklist.getSearchResults();
	for(unsigned int i = 0;i < searchedTask.size();i++){
		_deletedSearchedTasks.push_back(searchedTask[i]);
	}
}

void Command_Clear::saveFilteredTasks(TaskList &tasklist) {
	std::vector<Task*> filteredTask=tasklist.getFilterResults();
	for(unsigned int i = 0;i < filteredTask.size();i++){
		_deletedFilteredTasks.push_back(filteredTask[i]);
	}
}

void Command_Clear::repopulateSearchList(TaskList &tasklist){
	tasklist.resetSearchedTasks();
	for(unsigned int i = 0; i < _deletedSearchedTasks.size(); i++){
		tasklist.addTaskToSearchedList(*_deletedSearchedTasks[i]);
	}
}

void Command_Clear::repopulateFilterList(TaskList &tasklist){
	tasklist.resetFilteredTasks();
	for(unsigned int i = 0; i < _deletedFilteredTasks.size(); i++){
		tasklist.addTaskToFilteredList(*_deletedFilteredTasks[i]);
	}
}

void Command_Clear::createFeedback(std::string taskFeedback,std::string& feedback){
	feedback=taskFeedback;
}

bool Command_Clear::wasExecuted(){
	if(_lastCmdCalled==EXECUTE){
		return true;
	}
	return false;
}
void Command_Clear::permanantlyDeleteTasks(){
	for(unsigned int i = 0;i < _deletedUndoneTasks.size();i++){
		delete _deletedUndoneTasks[i];
		_deletedUndoneTasks[i] = NULL;
	}
}

void Command_Clear::lastCmdCalledIs(std::string cmd){
	_lastCmdCalled=cmd;
}

bool Command_Clear::wasUndone(){
	if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
		return true;
	}
	return false;
}

void Command_Clear::undoFilteredTasks(TaskList& tasklist, std::string& feedback){
	for(unsigned int i=0;i<_deletedFilteredTasks.size();i++){
		if(_deletedFilteredTasks[i]->getTaskStatus()==COMPLETED){
			tasklist.addTaskToDoneList(*_deletedFilteredTasks[i]);
		}else{
			tasklist.addTask(*_deletedFilteredTasks[i]);
		}
	}
	repopulateFilterList(tasklist);
	createFeedback(UNDO_CLEAR_FILTERED_SUCCESS,feedback);
}

void Command_Clear::undoSearchedTasks(TaskList& tasklist, std::string& feedback){
	for(unsigned int i=0;i<_deletedSearchedTasks.size();i++){
		if(_deletedSearchedTasks[i]->getTaskStatus()==COMPLETED){
			tasklist.addTaskToDoneList(*_deletedSearchedTasks[i]);
		}else{
			tasklist.addTask(*_deletedSearchedTasks[i]);
		}
	}
	repopulateSearchList(tasklist);
	createFeedback(UNDO_CLEAR_SEARCHED_SUCCESS,feedback);
}

void Command_Clear::undoScreenTasks(TaskList& tasklist, std::string& feedback){
	if(_displayScreen == COMPLETE){
		undoCompletedTasks(tasklist,feedback);
	} else if(_displayScreen==MAIN) {
		undoUncompletedTasks(tasklist,feedback);
	} else if(_displayScreen==FILTERED){
		undoFilteredTasks(tasklist,feedback);
	} else if(_displayScreen==SEARCHED){
		undoSearchedTasks(tasklist,feedback);
	}
}

