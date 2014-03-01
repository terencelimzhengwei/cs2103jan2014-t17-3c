#pragma once
#include "command.h"
class Command_Edit : public Command
{
public:
	Command_Edit() {
		init();
		setCommandType(EDIT);
	}
	~Command_Edit(void);
	std::string	getDescription(){ 
		return Command::getDescription();		
	}
	int getIndex() {
		return Command::getIndex();		
	}
	Date getDate(){
		return Command::getDate();	
	}
	ClockTime getStartTime(){ 
		return Command::getStartTime();		
	}
	ClockTime getEndTime(){ 
		return Command::getEndTime();		
	}

	PRIORITY getTaskPriority(){ 
		return Command::getTaskPriority();	
	}
	TASK_STATUS getTaskStatus(){
		return Command::getTaskStatus();
	}
	TASK_TYPE getTaskType() {
		return Command::getTaskType();
	}
	//setter for fields
	void setIndex(int taskIndex) {
		Command::setIndex(taskIndex);
	}
	void setDescription(std::string description){
		Command::setDescription(description);
	}
	void setPriority(PRIORITY taskPriority) {
		Command::setPriority(taskPriority);
	}
	void setCategory(std::string category) {
		Command:: setCategory(category);
	}
	void setDate(Date date) {
		Command::setDate(date);
	}
	void setStartTime(ClockTime startTime) {
		Command::setStartTime(startTime);
	}
	void setEndTime(ClockTime endTime) {
		Command::setEndTime(endTime);
	}
	void setTaskStatus(TASK_STATUS taskStatus) {
		Command::setTaskStatus(taskStatus);
	}
	void setTaskType(TASK_TYPE taskType) {
		Command::setTaskType(taskType);
	}

};

