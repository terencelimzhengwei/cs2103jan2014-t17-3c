#include "Task.h"

//@author A0097277M
Task::Task(void){
	initializeTask();
}

Task::~Task(void){
	resetPointers();
}

void Task::initializeTask(){
	_taskDescription=DEFAULT_EMPTY;
	_taskStatus = DEFAULT_TASK_STATUS;
	_category=DEFAULT_EMPTY;
	_startTime = NULL;
	_endTime = NULL;
	_startDate = NULL;
	_endDate = NULL;
	_clashStatus=false;
}

void Task::resetPointers(){
	if(!hasStartTime()){
		delete _startTime;
		_startTime=NULL;
	}
	if(!hasStartDate()){
		delete _startDate;
		_startDate=NULL;
	}
	if(!hasEndDate()){
		delete _endDate;
		_endDate=NULL;
	}
	if(!hasEndTime()){
		delete _endTime;
		_endTime=NULL;
	}
}

std::string Task::getDescription(){
	return _taskDescription;
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
void Task::setStartTime(ClockTime* startTime){
	_startTime = startTime;
}
void Task::setEndTime(ClockTime* endTime){
	_endTime = endTime;
}
void Task::setCategory(std::string category){
	_category = category;
}
void Task::setEndDate(Date* endDate){
	_endDate = endDate;
}
void Task::setStartDate(Date* startDate){
	_startDate = startDate;
}
void Task::setClash(bool clash){
	_clashStatus=clash;
}
void Task::setSchedule(Date* sDate,Date* eDate,ClockTime* sTime,ClockTime* eTime){
	setStartDate(sDate);
	setEndDate(eDate);
	setStartTime(sTime);
	setEndTime(eTime);
	checkInvalidDate();
	setTime();
	setDateBasedOnTime();
}
void Task::setDateBasedOnTime(){
	if(!hasEndDate()){
		setDateForFloatingTask();
	}else if(!hasStartDate()&&hasEndDate()){
		if(hasStartTime() && hasEndTime()){
			setDateForDeadlineTaskAccordingToTime();
		}
	}
}
void Task::setTime(){
	if(isDoubleDate()){
		if(!hasStartTime()&&hasEndTime()){
			_startTime=_endTime;
			_endTime=NULL;
		}
	}
	if(hasStartTime()&&hasEndTime()){
		if(*_startTime==*_endTime){
			if(!isDoubleDate()){
				delete _startTime;
				_startTime=NULL;
			}
		}
	}
}
void Task::editSchedule(ClockTime* sTime,ClockTime* eTime){
	setStartTime(sTime);
	setEndTime(eTime);
	setTime();
	setDateBasedOnTime();
}


bool Task::checkOverdue(){
	if(!hasEndDate()){
		return false;
	}else{
		if(_endDate->checkOverdue()==LATER){
			return true;
		}else if(_endDate->checkOverdue()==SAME){
			if(!hasEndTime()){
				return false;
			}else if(_endTime->checkOverdueTime()){
				return true;
			}
		}
	}
	return false;
}
bool Task::checkLater(Task* otherTask){
	if(!hasEndDate()){
		return false;
	}
	if(_endDate->isLater(otherTask->getEndDate())==LATER){
		return true;
	}else if(_endDate->isLater(otherTask->getEndDate())==EARLIER){
		return false;
	}else{
		if(!hasEndTime()){
			return false;
		}
		if(_endTime->isLater(otherTask->getEndTime())==LATER){
			return true;
		}else if(_endTime->isLater(otherTask->getEndTime())==EARLIER){
			return false;
		}
	}
	return true;
}
bool Task::checkClash(Task* task){
	bool clash=false;
	if(isSingleDate()&&task->isSingleDate()){
		checkClashForSingleDate(task, clash);
	}else if(isDoubleDate()&&task->isDoubleDate()){
		checkClashForDoubleDate(task, clash);
	}else if(isDoubleDate()&&task->isSingleDate()){
		checkClashDoubleDateSingleDate(task, clash);
	}else if(isSingleDate()&&task->isDoubleDate()){
		checkClashSingleDateDoubleDate(task, clash);
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
bool Task::checkTimeClashForDeadlineTask(Task* task){
	int sTime=DEFAULT_INDEX;
	int eTime=DEFAULT_INDEX;
	int othersTime = DEFAULT_INDEX;
	int othereTime = DEFAULT_INDEX;
	getTimeOfBothTaskInInt(sTime,eTime,othersTime,othereTime,task);

	if(isDoubleTime()&&task->isDoubleTime()){
		if(sTime<othereTime&&othersTime<eTime){
			return true;
		}
	}else if(isSingleTime()&&task->isDoubleTime()){
		if(eTime<othereTime&&eTime>othersTime){
			return true;
		}
	}else if(task->isSingleTime()&&isDoubleTime()){
		if(othereTime<eTime&&othereTime>sTime){
			return true;
		}
	}
	return false;
}
void Task::checkInvalidDate(){
	if(hasEndDate()&&hasStartDate()){
		if(*_endDate<*_startDate){
			throw InvalidStartEndDateTime();
		}else if(*_endDate==*_startDate){
			delete _startDate;
			_startDate=NULL;
		}
	}
}
bool Task::checkClashDate(Task* task){
	return *_startDate<*task->getEndDate() && *task->getStartDate()<*_endDate;
}

bool Task::hasKeyword(std::string keyword){
	unsigned int index;
	std::string keywordInLowerCase = keyword;
	std::string taskInLowerCase = _taskDescription;

	convertToLowerCase(keywordInLowerCase,taskInLowerCase);
	index = findIndexOfKeywordInString(taskInLowerCase,keywordInLowerCase);

	return isValidIndex(index);
}
bool Task::hasDate(Date* date){
	if(!hasEndDate()||date==NULL){
		return false;
	}
	if(!hasStartDate()){
		if(_endDate->compare(date)){
			return true;
		}
	}else{
		if(*date>=*_startDate&&*date<=*_endDate){
			return true;
		}
	}
	return false;
}
bool Task::hasCategory(std::string category){
	unsigned int index;
	std::string keywordInLowerCase = category;
	std::string categoryInLowerCase = _category;

	convertToLowerCase(keywordInLowerCase,categoryInLowerCase);
	index = findIndexOfKeywordInString(categoryInLowerCase,keywordInLowerCase);

	return isValidIndex(index);
}

void Task::resetClash(){
	_clashStatus=false;
}
bool Task::isClash(){
	return _clashStatus;
}
bool Task::isFloating(){
	if(!hasEndDate() && !hasStartDate() && !hasEndTime() && !hasStartTime()){
		return true;
	}
	return false;
}
bool Task::isSingleDate(){
	if(hasEndDate() && !hasStartDate()){
		return true;
	}
	return false;
}
bool Task::isDoubleDate(){
	if(hasEndDate() && hasStartDate()){
		return true;
	}
	return false;
}
bool Task::withTime(){
	if(hasStartTime()||hasEndTime()){
		return true;
	}
	return false;
}
std::string Task::getDayString(){
	if(hasStartDate()){
		if(_startDate->isToday()){
			return TODAY_DISPLAY;
		}else if(_startDate->isTomorrow()){
			return TMR_DISPLAY;
		}else{
			return _startDate->getDayOfTheWeek();
		}
	}else if(hasEndDate()){
		if(_endDate->isToday()){
			return TODAY_DISPLAY;
		}else if(_endDate->isTomorrow()){
			return TMR_DISPLAY;
		}else{
			return _endDate->getDayOfTheWeek();
		}
	}
	return DEFAULT_EMPTY;
}

bool Task::isSingleTime(){
	if(!hasStartTime()&&hasEndTime()||hasStartTime()&&!hasEndTime()){
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

bool Task::isDoubleTime(){
	if(hasStartTime()&&hasEndTime()){
		return true;
	}
	return false;
}

void Task::convertToLowerCase(std::string& keywordInLowerCase, std::string& taskInLowerCase){
	keywordInLowerCase=_parser.strToLower(keywordInLowerCase);
	taskInLowerCase=_parser.strToLower(taskInLowerCase);
}

unsigned int Task::findIndexOfKeywordInString(std::string taskInLowerCase, std::string keywordInLowerCase){
	return taskInLowerCase.find(keywordInLowerCase);
}

bool Task::isValidIndex(unsigned int index){
	if(index!=std::string::npos){
		return true;
	}
	return false;
}

void Task::getTimeOfBothTaskInInt(int& sTime, int& eTime, int& othersTime, int& othereTime, Task* task){
	if(hasStartTime()){
		sTime=_startTime->getTime();
	}if(hasEndTime()){
		eTime=_endTime->getTime();
	}if(task->hasEndTime()){
		othereTime=task->getEndTime()->getTime();
	}if(task->hasStartTime()){
		othersTime=task->getStartTime()->getTime();
	}
}

void Task::setDateForFloatingTask(){
	if(hasStartTime() && hasEndTime()){
		if(startTimeLaterThanEndTime()){
			setStartAndEndDateAcordingToTime();
		}else{
			setEndDateAccordingToStartTime();
		}
	}else if(!hasStartTime()&&hasEndTime()){
		setEndDateAccordingToEndTime();
	}
}

bool Task::startTimeLaterThanEndTime(){
	return *_startTime>*_endTime;
}

void Task::setStartAndEndDateAcordingToTime(){
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
}

void Task::setEndDateAccordingToStartTime(){
	if(_startTime->checkOverdueTime()){
		_endDate=new Date;
		_endDate->setDateAsTomorrow();
	}else{
		_endDate=new Date;
		_endDate->setDateAsToday();
	}     
}

void Task::setEndDateAccordingToEndTime(){
	if(_endTime->checkOverdueTime()){
		_endDate=new Date;
		_endDate->setDateAsTomorrow();
	}else{
		_endDate=new Date;
		_endDate->setDateAsToday();
	}     
}

void Task::setDateForDeadlineTaskAccordingToTime(){
	if(startTimeLaterThanEndTime()){
		_startDate=_endDate;
		_endDate=new Date(*_startDate);
		_endDate->setNextDay();
	}
}

void Task::checkClashForDoubleDate(Task* task, bool& clash){
	if(checkClashDate(task)){
		clash=true;
	}else if(*_startDate==*task->getEndDate()){
		if(hasStartTime()&&task->hasEndTime()){
			if(*_startTime<*_endTime){
				clash=true;
			}
		}
	}else if(_endDate==task->getStartDate()){
		if(hasEndTime()&&task->hasStartTime()){
			if(*_endTime>*_startTime){
				clash=true;
			}
		}
	}
}

void Task::checkClashForSingleDate(Task* task, bool& clash)
{
	if(*_endDate==*task->getEndDate()){
		if(isDoubleTime()&&task->isDoubleTime()){
			clash=checkTimeClashForDeadlineTask(task);
		}
	}
}

void Task::checkClashDoubleDateSingleDate(Task* task, bool& clash){
	if(*task->getEndDate()<*_endDate&&*task->getEndDate()>*_startDate){
		clash = true;
	}else if(*task->getEndDate()==*_startDate){
		if(hasStartTime()&&task->isDoubleTime()){
			if(*task->getStartTime()>*_startTime){
				clash = true;
			}
		}
	}else if(*task->getEndDate()==*_endDate){
		if(hasEndTime()&&task->isDoubleTime()){
			if(*task->getEndTime()<*_endTime){
				clash = true;
			}
		}
	}
}

void Task::checkClashSingleDateDoubleDate(Task* task, bool& clash){
	if(*task->getEndDate()>*_endDate&&*task->getStartDate()<*_endDate){
		clash = true;
	}else if(*task->getStartDate()==*_endDate){
		if(task->hasStartTime()&&isDoubleTime()){
			if(*task->getStartTime()>*_startTime){
				clash = true;
			}
		}
	}else if(*task->getEndDate()==*_endDate){
		if(task->hasEndTime()&&isDoubleTime()){
			if(*task->getEndTime()>*_endTime){
				clash = true;
			}
		}
	}
}
