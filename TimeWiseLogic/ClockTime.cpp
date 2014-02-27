#include "ClockTime.h"


ClockTime::ClockTime(){
}

ClockTime::ClockTime(int time){
	_time=time;

}


ClockTime::~ClockTime(void){
}



void ClockTime::setTimeNow(int time)
{
	_time=time;
}

bool ClockTime::checkOverdueTime(){
	bool hasElapsed;
	struct tm today;
	time_t currentTime = time(0);	// get local time
	int hr  = _time / 100,
		min = _time % 100;

	localtime_s( &today, &currentTime); // update tm struct to be local date and time

	if( hr < today.tm_hour ){
		hasElapsed = true;
	}
	else if ( hr == today.tm_hour && min < today.tm_min){
		hasElapsed = true; 
	}
	else{
		hasElapsed = false;
	}
	return hasElapsed;
}
