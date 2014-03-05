#pragma once
#include "Command_Add.h"

Command_Add::Command_Add() {
	_type = ADD;
	_taskIndex = DEFAULT_TASK_INDEX;
	_taskPriority = DEFAULT_PRIORITY;
	_taskType = DEFAULT_TASK_TYPE;
	_taskStatus = DEFAULT_TASK_STATUS;
	_category = DEFAULT_CATEGORY;
}
Command_Add::~Command_Add(void) {
}

//setter for fields
void Command_Add::setIndex(int taskIndex) {
	_taskIndex=taskIndex;
}
void Command_Add:: setDescription(std::string description){
	_taskDescription=description;
}
void Command_Add::setPriority(PRIORITY taskPriority) {
	_taskPriority=taskPriority;
}
void Command_Add::setCategory(std::string category) {
	_category=category;
}
void Command_Add::setStartDate(Date date) {
	_startDate=date;
}
void Command_Add::setStartTime(ClockTime startTime) {
	_startTime=startTime;
}
void Command_Add::setEndTime(ClockTime endTime) {
	_endTime=endTime;
}
void Command_Add:: setTaskStatus(TASK_STATUS taskStatus) {
	_taskStatus=taskStatus;
}
void Command_Add::setTaskType(TASK_TYPE taskType) {
	_taskType=taskType;
}

void Command_Add::setEndDate(Date date){
	_endDate=date;
}

bool Command_Add::execute(TaskList& tasklist){
	Task newTask;
	newTask.setDescription(_taskDescription);
	tasklist.addTask(newTask);
	return true;
}

bool Command_Add::undo(TaskList& tasklist){
	return true;
}



