#include "Command_AddEdit.h"


Command_AddEdit::Command_AddEdit(void){
	_type=ADDEDIT;
}


Command_AddEdit::~Command_AddEdit(void){
	if(_lastCmdCalled=="execute"){
		delete _deletedTask;
		_deletedTask=NULL;
	}else{
		_deletedTask=NULL;
	}
}

bool Command_AddEdit::execute(TaskList& tasklist){
	_addedTask = new Task;
	_addedTask->setDescription(_taskDescription);
	_addedTask->setPriority(_taskPriority);
	_addedTask->setCategory(_category);
	if(hasEndDate()){
		_addedTask->setEndDate(*_endDate);
	}
	if(hasEndTime()){
		_addedTask->setEndTime(*_endTime);
	}
	if(hasStartDate()){
		_addedTask->setStartDate(*_startDate);
	}
	if(hasStartTime()){
		_addedTask->setStartTime(*_startTime);
	}
	_addedTask->setTaskType(_taskType);
	tasklist.addTask(*_addedTask);
	if(_previousScreen==MAIN){
		_deletedTask=tasklist.deleteEditTask();
	}else if(_previousScreen==SEARCHED){
		_deletedTask=tasklist.deleteEditTaskFromSearch();
	}
	_lastCmdCalled="execute";
	return true;
}

bool Command_AddEdit::undo(TaskList& taskList){
	if (taskList.isEmpty()){
		return false;
	} else {
		int index = taskList.getTaskIndex(_addedTask);
		taskList.deleteTask(index);
		*_currentScreen=_previousScreen;
	}

	switch(_previousScreen){
	case MAIN:
		taskList.addTask(*_deletedTask);
		_lastCmdCalled="undo";
		break;
	case SEARCHED:
		taskList.addTask(*_deletedTask);
		std::vector<Task*>& searchResults=taskList.getSearchResults();
		searchResults.push_back(_deletedTask);
		_lastCmdCalled="undo";
		break;
	}
	return true;

}
