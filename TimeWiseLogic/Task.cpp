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
		if((date->isLater(_startDate)==SAME||date->isLater(_startDate)==LATER)
			&& (date->isLater(_endDate)==SAME||date->isLater(_endDate)==EARLIER))
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
	bool clash=false;
	if(isSingleDate()&&task->isSingleDate()){
		if(isDoubleTime()&&task->isDoubleTime()){
			clash=checkTimeClashForDeadlineTask(task);
		}
	}else if(isDoubleDate()&&task->isDoubleDate()){
		if(checkClashDate(task)){
			clash=true;
		}else if(_startDate==task->getEndDate()){
			if(hasStartTime()&&task->hasEndTime()){
				if(_startTime<_endTime){
					clash=true;
				}
			}
		}else if(_endDate==task->getStartDate()){
			if(hasEndTime()&&task->hasStartTime()){
				if(_endTime>_startTime){
					clash=true;
				}
			}
		}
	}else if(isDoubleDate()&&task->isSingleDate()){
		if(task->getEndDate()<_endDate&&task->getEndDate()>_startDate){
			clash = true;
		}else if(task->getEndDate()==_startDate){
			if(hasStartTime()&&task->isDoubleTime()){
				if(task->getStartTime()>_startTime){
					clash = true;
				}
			}
		}else if(task->getEndDate()==_endDate){
			if(hasEndTime()&&task->isDoubleTime()){
				if(task->getEndTime()<_endTime){
					clash = true;
				}
			}
		}
	}else if(isSingleDate()&&task->isDoubleDate()){
		if(task->getEndDate()>_endDate&&task->getStartDate()<_endDate){
			clash = true;
		}else if(task->getStartDate()==_endDate){
			if(task->hasStartTime()&&isDoubleTime()){
				if(task->getStartTime()<_startTime){
					clash = true;
				}
			}
		}else if(task->getEndDate()==_endDate){
			if(task->hasEndTime()&&isDoubleTime()){
				if(task->getEndTime()>_endTime){
					clash = true;
				}
			}
		}
	}
	return clash;
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

bool Task::checkTimeClashForDeadlineTask(Task* task){
	int sTime=DEFAULT_INDEX;
	int eTime=DEFAULT_INDEX;
	int othersTime = DEFAULT_INDEX;
	int othereTime = DEFAULT_INDEX;
	if(_startTime!=NULL){
		sTime=_startTime->getTime();
	}if(_endTime!=NULL){
		eTime=_endTime->getTime();
	}if(task->getEndTime()!=NULL){
		othereTime=task->getEndTime()->getTime();
	}if(task->getStartTime()!=NULL){
		othersTime=task->getStartTime()->getTime();
	}

	if(sTime!=DEFAULT_INDEX&&othersTime!=DEFAULT_INDEX&&eTime!=DEFAULT_INDEX&&othereTime!=DEFAULT_INDEX){
		if(sTime<othereTime&&othersTime<eTime){
			return true;
		}
	}else if(sTime==DEFAULT_INDEX&&eTime!=DEFAULT_INDEX&&othersTime!=DEFAULT_INDEX&&othereTime!=DEFAULT_INDEX){
		if(eTime<othereTime&&eTime>othersTime){
			return true;
		}
	}else if(othersTime==DEFAULT_INDEX&&othereTime!=DEFAULT_INDEX&&sTime!=DEFAULT_INDEX&&eTime!=DEFAULT_INDEX){
		if(othereTime<eTime&&othereTime>sTime){
			return true;
		}
	}
	return false;
}

void Task::setSchedule(Date* sDate,Date* eDate,ClockTime* sTime,ClockTime* eTime){
	_startDate=sDate;
	_endDate=eDate;
	_startTime=sTime;
	_endTime=eTime;

	checkInvalidDate();
	setTime();
	setDateBasedOnTime();
}

bool Task::isFloating(){
	if(_endDate==NULL && _startDate==NULL && _endTime==NULL && _startTime==NULL){
		return true;
	}
	return false;
}

bool Task::isSingleDate(){
	if(_endDate!=NULL && _startDate==NULL){
		return true;
	}
	return false;
}

void Task::checkInvalidDate(){
	if(_endDate!=NULL&&_startDate!=NULL){
		if(_endDate->isLater(_startDate)==EARLIER){
			throw InvalidStartEndDateTime();
		}else if(_endDate->isLater(_startDate)==SAME){
			delete _startDate;
			_startDate=NULL;
		}
	}
}

void Task::setDateBasedOnTime(){
	if(_endDate==NULL){
		if(_startTime!=NULL && _endTime!=NULL){
			if(_startTime->isLater(_endTime)==LATER){
				if(_startTime->checkOverdueTime()){
					_startDate=new Date;
					_startDate->setDateAsTomorrow();
					_endDate=new Date;
					_endDate->setDateAsDayAfterTomorrow();
				}else{
					_startDate=new Date;
					_startDate->setDateAsToday();
					_endDate=new Date;
					_endDate->setDateAsTomorrow();
				}
			}else{
				if(_startTime->checkOverdueTime()){
					_endDate=new Date;
					_endDate->setDateAsTomorrow();
				}else{
					_endDate=new Date;
					_endDate->setDateAsToday();
				}                       
			}
		}else if(_startTime==NULL&&_endTime!=NULL){
			if(_endTime->checkOverdueTime()){
				_endDate=new Date;
				_endDate->setDateAsTomorrow();
			}else{
				_endDate=new Date;
				_endDate->setDateAsToday();
			}
		}
	}else if(_startDate==NULL&&_endDate!=NULL){
		if(_startTime!=NULL && _endTime!=NULL){
			if(_startTime->isLater(_endTime)==LATER){
				_startDate=_endDate;
				_endDate=new Date(*_startDate);
				_endDate->setNextDay();
			}
		}
	}
}

void Task::setTime(){
	if(isDoubleDate()){
		if(_startTime==NULL&&_endTime!=NULL){
			_startTime=_endTime;
			_endTime=NULL;
		}
	}
	if(_startTime!=NULL&&_endTime!=NULL){
		if(_startTime->isLater(_endTime)==SAME){
			if(isDoubleDate()){
				delete _endTime;
				_endTime=NULL;
			}else{
				delete _startTime;
				_startTime=NULL;
			}
		}
	}
}

bool Task::isDoubleDate(){
	if(_endDate!=NULL && _startDate!=NULL){
		return true;
	}
	return false;
}

bool Task::withTime(){
	if(_startTime!=NULL||_endTime!=NULL){
		return true;
	}
	return false;
}

void Task::editSchedule(ClockTime* sTime,ClockTime* eTime){
	_startTime=sTime;
	_endTime=eTime;
	setTime();
	setDateBasedOnTime();
}

std::string Task::getDayString(){
	if(_startDate!=NULL){
		if(_startDate->isToday()){
			return "today";
		}else if(_startDate->isTomorrow()){
			return "tmrw";
		}else{
			return _startDate->getDayOfTheWeek();
		}
	}else if(_endDate!=NULL){
		if(_endDate->isToday()){
			return "today";
		}else if(_endDate->isTomorrow()){
			return "tmrw";
		}else{
			return _endDate->getDayOfTheWeek();
		}
	}
	return DEFAULT_EMPTY;
}

bool Task::isSingleTime()
{
	if(_startTime==NULL&&_endTime!=NULL||_startTime!=NULL&&_endTime==NULL){
		return true;
	}
	return false;
}

bool Task::hasStartTime(){
	if(_startTime!=NULL){
		return true;
	}
	return false;
}

bool Task::hasEndTime(){
	if(_endTime!=NULL){
		return true;
	}
	return false;
}

bool Task::hasEndDate(){
	if(_endDate!=NULL){
		return true;
	}
	return false;
}

bool Task::hasStartDate(){
	if(_startDate!=NULL){
		return true;
	}
	return false;
}

bool Task::isDoubleTime()
{
	if(_startTime!=NULL&&_endTime!=NULL){
		return true;
	}
	return false;
}

bool Task::checkClashDate(Task* task){
	bool chk1=_startDate<task->getEndDate();
	bool chk2=task->getStartDate()<_endDate;
	return _startDate->isLater(task->getEndDate())==EARLIER && task->getStartDate()->isLater(_endDate)==EARLIER;
}

