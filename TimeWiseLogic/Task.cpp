
#include "Task.h"


Task::Task(void){
	_taskDescription=DEFAULT_EMPTY;
	_taskType = DEFAULT_TASK_TYPE;
	_taskStatus = DEFAULT_TASK_STATUS;
	_taskPriority=DEFAULT_PRIORITY;
	_category=DEFAULT_EMPTY;
	_startTime = NULL;
	_endTime = NULL;
	_startDate = NULL;
	_endDate = NULL;
	_taskIndex= DEFAULT_INDEX;
	_clashStatus=false;
	_blockStatus=false;
}


Task::~Task(void){
	if(_startTime!=NULL){
		delete _startTime;
		_startTime=NULL;
	}
	if(_startDate!=NULL){
		delete _startDate;
		_startTime=NULL;
	}
	if(_endDate!=NULL){
		delete _endDate;
		_startTime=NULL;
	}
	if(_endTime!=NULL){
		delete _endTime;
		_startTime=NULL;
	}
}

std::string Task::getDescription(){
	return _taskDescription;
}
int Task::getIndex(){
	return _taskIndex;
}

void Task::setDescription(std::string desc){
	_taskDescription = desc;
}

void Task::setStatusAsDone(){
	_taskStatus = COMPLETED;
}

void Task::setStatusasUndone(){
	_taskStatus = UNCOMPLETED;
}

void Task::setStatusAsOverdue(){
	_taskStatus= OVERDUE;
}

bool Task::checkOverdue()
{
	if(_endDate==NULL){
		return false;
	}else{
		if(_endDate->checkOverdue()==LATER){
			return true;
		}else if(_endDate->checkOverdue()==SAME){
			if(_endTime==NULL){
				return false;
			}else if(_endTime->checkOverdueTime()){
				return true;
			}
		}
	}
	return false;
}

void Task::setTaskType(TASK_TYPE type){
	_taskType = type;
}

Date* Task::getEndDate(){
	return _endDate;
}
Date* Task::getStartDate(){
	return _startDate;
}

ClockTime* Task::getEndTime(){
	return _endTime;
}

ClockTime* Task::getStartTime(){
	return _startTime;
}

TASK_STATUS Task::getTaskStatus(){
	return _taskStatus;
}

std::string Task::getTaskCategory(){
	return _category;
}

void Task::setStartTime(ClockTime* startTime)
{
	_startTime = startTime;
}
void Task::setEndTime(ClockTime* endTime)
{
	_endTime = endTime;
}

void Task::setPriority(PRIORITY taskPriority){
	_taskPriority = taskPriority;
}

void Task::setCategory(std::string category){
	_category = category;
}

void Task::setIndex(int index){ 
	assert(index>=0);
	_taskIndex = index;
}
void Task::setEndDate(Date* endDate){
	_endDate = endDate;
}
void Task::setStartDate(Date* startDate)
{
	_startDate = startDate;
}

bool Task::hasKeyword(std::string keyword){
	unsigned int index;
	std::string keywordInLowerCase = keyword;
	std::string taskInLowerCase = _taskDescription;

	transform(keywordInLowerCase.begin(), keywordInLowerCase.end(), keywordInLowerCase.begin(), ::tolower);
	transform(taskInLowerCase.begin(), taskInLowerCase.end(), taskInLowerCase.begin(), ::tolower);

	index=taskInLowerCase.find(keywordInLowerCase);

	if(index!=std::string::npos){
		return true;
	}
	return false;
}

PRIORITY Task::getPriority(){
	return _taskPriority;
}

bool Task::checkLater(Task* otherTask){
	if(_endDate==NULL){
		return false;
	}
	assert(_endDate!=NULL);
	if((_endDate->isLater(otherTask->getEndDate()))==LATER){
		return true;
	}else if((_endDate->isLater(otherTask->getEndDate()))==EARLIER){
		return false;
	}else{
		if(_endTime==NULL){
			return false;
		}
		assert(_endTime!=NULL);
		if((_endTime->isLater(otherTask->getEndTime()))==LATER){
			return true;
		}else if((_endTime->isLater(otherTask->getEndTime()))==EARLIER){
			return false;
		}
	}
	return true;
}

bool Task::hasPriority(PRIORITY priority){
	if(_taskPriority==priority){
		return true;
	}
	return false;
}

bool Task::hasDate(Date* date){
	if(_endDate==NULL||date==NULL){
		return false;
	}
	if(_startDate==NULL){
		if(_endDate->compare(date)){
			return true;
		}
	}else{
		if(date->isLater(_startDate)==SAME||date->isLater(_startDate)==LATER
			&& date->isLater(_endDate)==SAME||date->isLater(_endDate)==EARLIER)
			return true;
	}
	return false;
}

bool Task::hasCategory(std::string category){
	unsigned int index;
	std::string keywordInLowerCase = category;
	std::string categoryInLowerCase = _category;

	transform(keywordInLowerCase.begin(), keywordInLowerCase.end(), keywordInLowerCase.begin(), ::tolower);
	transform(categoryInLowerCase.begin(), categoryInLowerCase.end(), categoryInLowerCase.begin(), ::tolower);

	index=categoryInLowerCase.find(keywordInLowerCase);

	if(index!=std::string::npos){
		return true;
	}
	return false;
}

bool Task::hasStatus(TASK_STATUS status){
	if(_taskStatus==status){
		return true;
	}
	return false;
}

bool Task::checkClash(Task* task){
	if(_endDate==NULL||task->getEndDate()==NULL){
		return false;
	}else if(_startDate==NULL && task->getStartDate()==NULL){
		if(_endDate->isLater(task->getEndDate())==SAME){
			return checkClashTime(task);
		}
	}else if(_startDate==NULL){
		if(_endDate->isLater(task->getEndDate())==EARLIER||_endDate->isLater(task->getEndDate())==SAME){
			if(_endDate->isLater(task->getStartDate())==LATER||_endDate->isLater(task->getStartDate())==SAME){
				return checkClashTime(task);
			}
		}
	}else if(task->getStartDate()==NULL){
		if(task->getEndDate()->isLater(_endDate)==EARLIER||task->getEndDate()->isLater(_endDate)==SAME){
			if(task->getEndDate()->isLater(_startDate)==LATER||task->getEndDate()->isLater(_startDate)==SAME){
				return checkClashTime(task);
			}
		}
	}else{
		if(_startDate->isLater(task->getEndDate())==EARLIER||_startDate->isLater(task->getEndDate())==SAME){
			if(task->getStartDate()->isLater(_endDate)==EARLIER||task->getStartDate()->isLater(_endDate)==SAME){
				return checkClashTime(task);
			}
		}
	}
	return false;
}

bool Task::checkNewOverdue(){
	if(checkOverdue()){
		if(getTaskStatus()!=OVERDUE){
			setStatusAsOverdue();
			return true;
		}
	}else{
		if(getTaskStatus()==OVERDUE){
			setStatusasUndone();
			return true;
		}
	}
	return false;
}

std::string Task::toString(){
	std::string description = _taskDescription;
	std::string startDate="";
	std::string endDate="";
	std::string endTime="";
	std::string startTime="";
	std::string priority="";
	std::string category="";

	if(_startDate!=NULL){
		startDate=_startDate->toFormat();
	}
	if(_endDate!=NULL){
		endDate=_endDate->toFormat();
	}
	if(_startTime!=NULL){
		startTime=_startTime->toString();
	}
	if(_endTime!=NULL){
		endTime=_endTime->toString();
	}
	priority=PRIORITY_STRING[_taskPriority];
	category=_category;

	std::string command = description;
	if(startDate!=""&&endDate!=""){
		description+=" on ";
		description+=startDate;
		description+=" to ";
		description+=endDate;
	}else if(endDate!=""){
		description+=" on ";
		description+=endDate;
	}

	if(startTime!=""&&endTime!=""){
		description+=" from ";
		description+=startTime;
		description+=" to ";
		description+=endTime;
	}else if(endTime!=""){
		description+=" at ";
		description+=endTime;
	}

	if(priority!=""){
		description+=" !"+priority;
	}
	if(category!=""){
		description+=" #"+category;
	}

	return description;
}

void Task::resetClash(){
	_clashStatus=false;
}

bool Task::isClash(){
	return _clashStatus;
}

void Task::setClash(bool clash){
	_clashStatus=clash;
}

bool Task::checkClashTime(Task* task){
	if(_endTime==NULL && task->getEndTime()==NULL){
		return true;
	}

	if(_endTime==NULL||task->getEndTime()==NULL){
		return false;
	}else if(_startTime==NULL && task->getStartTime()==NULL){
		if(_endTime->isLater(task->getEndTime())==SAME){
			return true;
		}
	}else if(_startTime==NULL){
		if(_endTime->isLater(task->getEndTime())==EARLIER||_endTime->isLater(task->getEndTime())==SAME){
			if(_endTime->isLater(task->getStartTime())==LATER||_endTime->isLater(task->getStartTime())==SAME){
				return true;
			}
		}
	}else if(task->getStartTime()==NULL){
		if(task->getEndTime()->isLater(_endTime)==EARLIER||task->getEndTime()->isLater(_endTime)==SAME){
			if(task->getEndTime()->isLater(_startTime)==LATER||task->getEndTime()->isLater(_startTime)==SAME){
				return true;
			}
		}
	}else{
		if(_startTime->isLater(task->getEndTime())==EARLIER||_startTime->isLater(task->getEndTime())==SAME){
			if(task->getStartTime()->isLater(_endTime)==EARLIER||task->getStartTime()->isLater(_endTime)==SAME){
				return true;
			}
		}
	}
	return false;
}

void Task::setBlockStatus(bool status){
	_blockStatus=true;
}
