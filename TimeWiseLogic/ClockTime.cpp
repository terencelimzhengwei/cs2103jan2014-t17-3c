#include "ClockTime.h"


ClockTime::ClockTime(){
}

ClockTime::ClockTime(int time){
	_time=time;

}

ClockTime::ClockTime(ClockTime& time){
	_time= time._time;
}


ClockTime::~ClockTime(void){
}



void ClockTime::setTimeNow(int time){
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

std::string ClockTime::toString(){
	std::ostringstream stream;
	int timeInt = _time;
	stream<<_time;
	std::string timeInString;
	timeInString = stream.str();

	switch(timeInString.size()){
	case 1:
		if(timeInString[0]=='0'){
			return "0000";
		}else{
			return "000"+timeInString;
		}
		break;
	case 2:
		return "00"+timeInString;
	case 3:
		return "0"+timeInString;
	default:
		return timeInString;
	}
}
TIMEDATE_STATUS ClockTime::isLater(ClockTime* otherTime)
{
	if(otherTime==NULL){
		return LATER;
	}else if(_time>otherTime->getTime()){
		return LATER;
	}else if(_time==otherTime->getTime()){
		return SAME;
	}
	return EARLIER;
}

int ClockTime::getTime(){
	return _time;
}