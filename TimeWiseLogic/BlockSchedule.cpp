#include "BlockSchedule.h"


BlockSchedule::BlockSchedule(void){
}

BlockSchedule::BlockSchedule(Date* startDate,Date* endDate,ClockTime* startTime,ClockTime* endTime){
	_startTime=startTime;
	_endDate=endDate;
	_endTime=endTime;
	_startDate=startDate;
}


BlockSchedule::~BlockSchedule(void){
}

Date* BlockSchedule::getEndDate(){
	return _endDate;
}

Date* BlockSchedule::getStartDate(){
	return _startDate;
}

ClockTime* BlockSchedule::getStartTime(){
	return _startTime;
}

ClockTime* BlockSchedule::getEndTime(){
	return _endTime;
}
