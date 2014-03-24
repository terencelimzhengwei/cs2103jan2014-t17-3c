#pragma once
#include "Task.h"
class Clash
{
public:
	Clash(void);
	Clash(Task* task1, Task* task2);
	~Clash(void);

	Task* getFirstTask();
	Task* getSecondTask();
private:
	Task* _task1;
	Task* _task2;
};

