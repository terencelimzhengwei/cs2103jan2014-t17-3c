#pragma once

#ifndef COMMAND_H
#define COMMAND_H

// TiMEWiSE Command Base Class
//I dont really understand what exactly the flag methods do
//Will update once I pick it up
#include <list>
#include <string>
#include "Date.h"
#include "ClockTime.h"
#include "Constants.h"
#include "Command_Add.h"
#include "Command_Edit.h"
#include "Command_Delete.h"
#include "Command_Display.h"

class Command
{
public:
	Command(void);
	~Command(void);

	void init();
					
	CMD_TYPE getCommandType() {
		return _type;
	}

protected:
	void setCommandType (CMD_TYPE type) {
		_type = type;
	}

	//getter for fields
	int getIndex () {
		return _taskIndex;
	}
	std::string getDescription() {
		return _taskDescription;
	}
	Date getDate() {
		return _date;
	} 
	ClockTime getEndTime() {
		return _endTime;
	}

	ClockTime getStartTime(){
		return _startTime;
	}

	TASK_STATUS getTaskStatus(){
		return _taskStatus;
	}
	PRIORITY getTaskPriority() {
		return _taskPriority;
	}
	std::string getTaskCategory(){
		return _category;
	}
	TASK_TYPE getTaskType() {
		return _taskType;
	}
	//setter for fields  
	void setIndex(int taskIndex) {
		_taskIndex = taskIndex;
	}
	void setDescription(std::string description){
		_taskDescription = description;
	}
	void setPriority(PRIORITY taskPriority) {
		_taskPriority = taskPriority;
	}
	void setCategory(std::string category) {
		_category = category;
	}
	void setDate(Date date) {
		_date = date;
	}
	void setStartTime(ClockTime startTime) {
		_startTime = startTime;
	}
	void setEndTime(ClockTime endTime) {
		_endTime = endTime;
	}
	void setTaskStatus(TASK_STATUS taskStatus) {
		_taskStatus = taskStatus;
	}
	void setTaskType(TASK_TYPE taskType) {
		_taskType = taskType;
	}

	
private:
	static const CMD_TYPE DEFAULT_COMMAND_TYPE;
	static const PRIORITY DEFAULT_PRIORITY;
	static const TASK_STATUS DEFAULT_TASK_STATUS;
	static const TASK_TYPE	DEFAULT_TASK_TYPE;
	static const int DEFAULT_TASK_INDEX;
	static const std::string DEFAULT_CATEGORY;
	
	//fields
	CMD_TYPE _type;
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	PRIORITY _taskPriority;
	std::string _category;
	unsigned long long _taskIndex;

	Date _date;
	ClockTime _startTime;
	ClockTime _endTime;
	
};

#endif