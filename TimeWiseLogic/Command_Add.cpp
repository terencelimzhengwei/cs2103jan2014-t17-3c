#pragma once
#include "Command_Add.h"

Command_Add::Command_Add() {
		init();
		setCommandType(ADD);
}
Command_Add::~Command_Add(void) {
}

std::string Command_Add::getDescription(){ 
		return Command::getDescription();		
}
unsigned long long Command_Add:: getIndex() {
		return Command::getIndex();		
}
Date Command_Add:: getDate(){
		return Command::getDate();	
}
ClockTime Command_Add::getStartTime(){ 
		return Command::getStartTime();		
}
ClockTime Command_Add:: getEndTime(){ 
		return Command::getEndTime();		
}

PRIORITY Command_Add:: getTaskPriority(){ 
		return Command::getTaskPriority();	
}
TASK_STATUS Command_Add:: getTaskStatus(){
		return Command::getTaskStatus();
}
TASK_TYPE Command_Add:: getTaskType() {
		return Command::getTaskType();
}
	//setter for fields
void Command_Add::setIndex(int taskIndex) {
		Command::setIndex(taskIndex);
}
void Command_Add:: setDescription(std::string description){
		Command::setDescription(description);
}
void Command_Add::setPriority(PRIORITY taskPriority) {
		Command::setPriority(taskPriority);
}
void Command_Add::setCategory(std::string category) {
		Command:: setCategory(category);
}
void Command_Add::setDate(Date date) {
		Command::setDate(date);
}
void Command_Add::setStartTime(ClockTime startTime) {
		Command::setStartTime(startTime);
	}
void Command_Add::setEndTime(ClockTime endTime) {
		Command::setEndTime(endTime);
}
void Command_Add:: setTaskStatus(TASK_STATUS taskStatus) {
		Command::setTaskStatus(taskStatus);
}
void Command_Add::setTaskType(TASK_TYPE taskType) {
		Command::setTaskType(taskType);
}



