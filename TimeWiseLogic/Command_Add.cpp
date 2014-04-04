#pragma once
#include "Command_Add.h"

//***************************************************************************************
//When a new Command_Add object is dynamically created, it will set _setPriority to LOW,
//_taskType to FLOATING and _category to "". 
//This means that, when a task with only description is entered, it's priority, type and
//category will be set to these default values.
//***************************************************************************************
Command_Add::Command_Add() {
	_type = ADD;	
	_taskPriority = DEFAULT_PRIORITY;
	_taskType = DEFAULT_TASK_TYPE;
	_category = DEFAULT_EMPTY;
	_endDate = NULL;
	_endTime = NULL;
	_startDate = NULL;
	_startTime = NULL;
	_addedTask = NULL;
	_currentScreen = NULL;
}
Command_Add::~Command_Add(void) {
	if(_startTime != NULL){
		_startTime = NULL;
	}
	if(_startDate != NULL){
		_startTime = NULL;
	}
	if(_endDate != NULL){
		_startTime = NULL;
	}
	if(_endTime != NULL){
		_startTime = NULL;
	}
	_addedTask = NULL;

}

//setter for fields
void Command_Add:: setDescription(std::string description){
	_taskDescription = description;
}
void Command_Add::setPriority(PRIORITY taskPriority) {
	_taskPriority = taskPriority;
}
void Command_Add::setCategory(std::string category) {
	_category = category;
}
void Command_Add::setStartDate(Date& date) {
	_startDate = new Date(date);
}
void Command_Add::setStartTime(ClockTime& startTime) {
	_startTime = new ClockTime(startTime);
}
void Command_Add::setEndTime(ClockTime& endTime) {
	_endTime = new ClockTime(endTime);
}
void Command_Add::setTaskType(TASK_TYPE taskType) {
	_taskType = taskType;
}

void Command_Add::setEndDate(Date& date)
{
	_endDate = new Date(date);
}

bool Command_Add::execute(TaskList& tasklist,std::string& feedback){
	*_currentScreen = MAIN;
	//Check whether the previous command was deleting a task and the user tries to undo this, 
	//the task will added back to tasklist.
	if(_lastCmdCalled == CMD_TYPE_STRING[8]){
		tasklist.addTask(*_addedTask);
	} else {
		_addedTask = new Task;
		_addedTask->setDescription(_taskDescription);
		_addedTask->setPriority(_taskPriority);
		_addedTask->setCategory(_category);
		if(hasEndDate()){
			_addedTask->setEndDate(_endDate);
		}
		if(hasEndTime()){
			_addedTask->setEndTime(_endTime);
		}
		if(hasStartDate()){
			_addedTask->setStartDate(_startDate);
		}
		if(hasStartTime()){
			_addedTask->setStartTime(_startTime);
		}
		_addedTask->setTaskType(_taskType);
		tasklist.addTask(*_addedTask);
	}
	_lastCmdCalled == CMD_TYPE_STRING[12];
	feedback = TASK + _addedTask->toString() + ADD_SUCCESS;
	return true;
}

bool Command_Add::undo(TaskList& taskList){
	if (taskList.isEmpty()){
		return false;
	} else {
		unsigned int index = taskList.getTaskIndex(_addedTask);
		taskList.deleteTask(index);
		*_currentScreen = _previousScreen;
		_lastCmdCalled = CMD_TYPE_STRING[8];
		return true;
	}
}

bool Command_Add::hasEndDate(){
	if(_endDate == NULL){
		return false;
	}
	return true;
}

bool Command_Add::hasStartDate(){
	if(_startDate == NULL){
		return false;
	}
	return true;
}

bool Command_Add::hasStartTime(){
	if(_startTime == NULL){
		return false;
	}
	return true;
}

bool Command_Add::hasEndTime(){
	if(_endTime == NULL){
		return false;
	}
	return true;
}

void Command_Add::setPreviousScreen(DISPLAY_TYPE* screen){	
	_previousScreen = *screen;
	_currentScreen = screen;
}

