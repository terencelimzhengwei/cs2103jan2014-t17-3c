#pragma once
#include "Command_Edit.h"


Command_Edit::Command_Edit() {
		init();
		setCommandType(EDIT);
}
Command_Edit::~Command_Edit(){};
	std::string Command_Edit::getDescription(){ 
		return Command::getDescription();		
}
	unsigned long long Command_Edit::getIndex() {
		return Command::getIndex();		
}
	Date Command_Edit::getDate(){
		return Command::getDate();	
}
	ClockTime Command_Edit::getStartTime(){ 
		return Command::getStartTime();		
}
	ClockTime Command_Edit::getEndTime(){ 
		return Command::getEndTime();		
}

	PRIORITY Command_Edit::getTaskPriority(){ 
		return Command::getTaskPriority();	
}
	TASK_STATUS Command_Edit::getTaskStatus(){
		return Command::getTaskStatus();
}
	TASK_TYPE Command_Edit::getTaskType() {
		return Command::getTaskType();
	}
	//setter for fields
void Command_Edit::setIndex(int taskIndex) {
		Command::setIndex(taskIndex);
	}
void Command_Edit::setDescription(std::string description){
		Command::setDescription(description);
	}
void Command_Edit::setPriority(PRIORITY taskPriority) {
		Command::setPriority(taskPriority);
	}
void Command_Edit::setCategory(std::string category) {
		Command:: setCategory(category);
	}
void Command_Edit::setDate(Date date) {
		Command::setDate(date);
	}
void Command_Edit::setStartTime(ClockTime startTime) {
		Command::setStartTime(startTime);
	}
void Command_Edit::setEndTime(ClockTime endTime) {
		Command::setEndTime(endTime);
	}
void Command_Edit::setTaskStatus(TASK_STATUS taskStatus) {
		Command::setTaskStatus(taskStatus);
	}
void Command_Edit::setTaskType(TASK_TYPE taskType) {
		Command::setTaskType(taskType);
	}



