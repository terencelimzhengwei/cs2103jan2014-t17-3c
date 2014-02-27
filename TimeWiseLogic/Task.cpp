
#include "Task.h"


Task::Task(void){
	_taskDescription="";
	_taskType = FLOATING;
	_taskStatus = UNDONE;
}


Task::~Task(void){
}

std::string Task::getDescription(){
	return _taskDescription;
}

void Task::setDescription(std::string desc){
	_taskDescription=desc;
}

void Task::setStatusAsDone(){
	_taskStatus=DONE;
}

void Task::setStatusAsOverdue(){
	_taskStatus=OVERDUE;
}

bool Task::checkOverdue()
{
	bool overdue = false;
	if(_date.checkOverdue()){
		return true;
	}
	else{
		if(_endTime.checkOverdueTime()){
			return true;
		}
	}
	if(overdue==true){
		setStatusAsOverdue();
	}
	return false;
}

void Task::setTaskType(TASK_TYPE type){
	_taskType=type;
}

Date Task::getDate(){
	return _date;
}

ClockTime Task::getEndTime()
{
	return _endTime;
}

ClockTime Task::getStartTime()
{
	return _startTime;
}

TASK_STATUS Task::getTaskStatus()
{
	return _taskStatus;
}

std::string Task::getTaskCategory()
{
	return _category;
}

void Task::setDate(Date date)
{
	_date=date;
}

void Task::setStartTime(ClockTime startTime)
{
	_startTime=startTime;
}
void Task::setEndTime(ClockTime endTime)
{
	_endTime=endTime;
}

void Task::setPriority(PRIORITY taskPriority)
{
	_taskPriority=taskPriority;
}

void Task::setCategory(std::string category)
{
	_category=category;
}

