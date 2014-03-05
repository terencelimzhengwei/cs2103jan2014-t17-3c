#pragma once
#include "Command_Edit.h"


Command_Edit::Command_Edit() {
	_type = EDIT;
	_taskIndex = DEFAULT_TASK_INDEX;
	_taskPriority = DEFAULT_PRIORITY;
	_taskType = DEFAULT_TASK_TYPE;
	_taskStatus = DEFAULT_TASK_STATUS;
	_category = DEFAULT_CATEGORY;
}
Command_Edit::~Command_Edit(){
}

void Command_Edit::setIndex(int taskIndex) {
	_taskIndex=taskIndex;
}
void Command_Edit::setDescription(std::string description){
	_taskDescription=description;
}
void Command_Edit::setPriority(PRIORITY taskPriority) {
	_taskPriority=taskPriority;
}
void Command_Edit::setCategory(std::string category) {
	_category=category;
}
void Command_Edit::setStartDate(Date date) {
	_startDate=date;
}
void Command_Edit::setStartTime(ClockTime startTime) {
	_startTime=startTime;
}
void Command_Edit::setEndTime(ClockTime endTime) {
	_endTime=endTime;
}
void Command_Edit::setTaskStatus(TASK_STATUS taskStatus) {
	_taskStatus=taskStatus;
}
void Command_Edit::setTaskType(TASK_TYPE taskType) {
	_taskType=taskType;
}

void Command_Edit::setEndDate(Date date){
	_endDate=date;
}

bool Command_Edit::execute(TaskList& tasklist){
	return true;
}

bool Command_Edit::undo(TaskList& taskList){
	return true;
}



