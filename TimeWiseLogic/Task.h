#pragma once

#include "Constants.h"
#include <string>

class Task
{
public:
	Task(void);
	~Task(void);

/*
	//getter functions
	TASK_TYPE			getTaskType()		const { return _taskType;			}
	std::string				getDescription()	const { return _taskDescription;	}		
	std::list<std::string>	getCategory()		const { return _taskTags;			}
	std::list<std::time_t>	getRemindTimes()	const { return _taskRemindTimes;	}
	TASK_STATE			getState()			const { return _taskState;			}
	PRIORITY			getPriority()		const { return _taskPriority;		}
	unsigned long long		getIndex()			const { return _taskIndex;			}
	std::time_t				getFromDate()		const { return _taskFromDate;		}
	std::time_t				getToDate()			const { return _taskToDate;			}
	std::time_t				getDueDate()		const { return _taskFromDate;		}*/
	std::string getDescription();
	void addDescription(std::string desc);
private:
	std::string _taskDescription;
	TASK_TYPE _taskType;
	TASK_STATUS _taskStatus;
	//PRIORITY _taskPriority;
	//std::string category;
	//std::string _taskDate;
	//std::string	_taskStartTime;
	//std::string	_taskEndTime;
	//unsigned long long _taskIndex;
};