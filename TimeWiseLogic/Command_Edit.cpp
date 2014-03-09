#pragma once
#include "Command_Edit.h"


Command_Edit::Command_Edit() {
	_type = EDIT;
	_taskIndex = DEFAULT_INDEX;
	_taskPriority = DEFAULT_PRIORITY;
	_category = DEFAULT_EMPTY;
	_taskEdited=NULL;
	_startTime=NULL;
	_startDate=NULL;
	_endTime=NULL;
	_endDate=NULL;
}
Command_Edit::~Command_Edit(){
}

void Command_Edit::setIndex(unsigned int taskIndex) {
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
void Command_Edit::setStartDate(Date& startDate)
{
	_startDate = &startDate;
}
void Command_Edit::setStartTime(ClockTime& startTime)
{
	_startTime = &startTime;
}
void Command_Edit::setEndTime(ClockTime& endTime)
{
	_endTime = &endTime;
}

void Command_Edit::setEndDate(Date& endDate)
{
	_endDate = &endDate;
}

bool Command_Edit::execute(TaskList& taskList){

	_taskEdited = taskList.getTask(_taskIndex);
	_originalTask=*_taskEdited;
	if(_header=="description"){
		_taskEdited->setDescription(_taskDescription);
		return true;
	}else if(_header=="start date"){
		_taskEdited->setStartDate(*_startDate);
		return true;
	}else if(_header=="end date"){
		_taskEdited->setEndDate(*_endDate);
		return true;
	}else if(_header=="priority"){
		_taskEdited->setPriority(_taskPriority);
		return true;
	}else if(_header=="category"){
		_taskEdited->setCategory(_category);
		return true;
	}else if(_header=="start time"){
		_taskEdited->setStartTime(*_startTime);
		return true;
	}else if(_header=="end time"){
		_taskEdited->setEndTime(*_endTime);
		return true;
	}
	return false;
}

bool Command_Edit::undo(TaskList& taskList){
	if(_header=="description"){
		_taskEdited->setDescription(_originalTask.getDescription());
	}else if(_header=="start date"){
		_taskEdited->setStartDate(_originalTask.getStartDate());
	}else if(_header=="end date"){
		_taskEdited->setEndDate(_originalTask.getEndDate());
	}else if(_header=="priority"){
		_taskEdited->setPriority(_originalTask.getPriority());
	}else if(_header=="category"){
		_taskEdited->setCategory(_originalTask.getTaskCategory());
	}else if(_header=="start time"){
		_taskEdited->setStartTime(_originalTask.getStartTime());
	}else if(_header=="end time"){
		_taskEdited->setEndTime(_originalTask.getEndTime());
	}
	return true;
}

void Command_Edit::setHeader(std::string header){
	_header=header;
}



