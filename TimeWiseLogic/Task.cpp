
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

void Task::addDescription(std::string desc){
	_taskDescription=desc;
}