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
	_taskIndex = taskIndex;
}
void Command_Edit::setDescription(std::string description){
	_taskDescription = description;
}
void Command_Edit::setPriority(PRIORITY taskPriority) {
	_taskPriority = taskPriority;
}
void Command_Edit::setCategory(std::string category) {
	_category = category;
}
void Command_Edit::setStartDate(Date date) {
	_startDate = date;
}
void Command_Edit::setStartTime(ClockTime startTime) {
	_startTime = startTime;
}
void Command_Edit::setEndTime(ClockTime endTime) {
	_endTime = endTime;
}
void Command_Edit::setTaskStatus(TASK_STATUS taskStatus) {
	_taskStatus = taskStatus;
}
void Command_Edit::setTaskType(TASK_TYPE taskType) {
	_taskType = taskType;
}

void Command_Edit::setEndDate(Date date){
	_endDate = date;
}

bool Command_Edit::execute(TaskList& taskList){
	unsigned int index = _taskIndex - 1;
	if (taskList.isEmpty()) {
		return false;
	} else if(index < 0 || index > taskList.size() - 1) {
		return false;
	} else {
		Task temp = taskList.getTask(index);
		_beforeEdit.push(temp);
		temp.setDescription(_taskDescription);
		temp.setStartDate(_startDate);
		temp.setEndDate(_endDate);
		temp.setPriority(_taskPriority);
		temp.setCategory(_category);
		temp.setStartTime(_startTime);
		temp.setEndTime(_endTime);
		temp.setTaskType(_taskType);
		switch(_taskStatus) {
		case COMPLETED:
		temp.setStatusAsDone();
		case UNCOMPLETED:
		temp.setStatusasUndone();
		case OVERDUE:
		temp.setStatusAsOverdue();
		default:
		break;
		}
		bool deleteOldTask = taskList.deleteTask(_taskIndex);
		//add the edited task into the list
		taskList.addTask(_taskIndex,temp);
	}
	return true;
}

bool Command_Edit::undo(TaskList& taskList){
	Task temp = _beforeEdit.top();
	taskList.deleteTask(_taskIndex);
	taskList.addTask(_taskIndex, temp);
	_beforeEdit.pop();
	return true;
}



