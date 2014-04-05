#pragma once
#include "ClockTime.h"
#include "Date.h"

class BlockSchedule{
public:
	BlockSchedule(void);
	BlockSchedule(Date* startDate,Date* endDate,ClockTime* startTime,ClockTime* endTime);
	~BlockSchedule(void);
	Date* getEndDate();
	Date* getStartDate();
	ClockTime* getStartTime();
	ClockTime* getEndTime();
private:
	Date* _endDate;
	Date* _startDate;
	ClockTime* _startTime;
	ClockTime* _endTime;
};

