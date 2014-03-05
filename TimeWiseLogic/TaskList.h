#pragma once

#include <vector>
#include "Task.h"

class TaskList
{
public:
	TaskList(void);
	~TaskList(void);

	void addTask(Task);
	void addTask(unsigned int, Task);
	Task getTask(unsigned int);
	bool deleteTask(unsigned int&);
	//void clearTask();
	//std::string searchTask(std::string& keyWord);
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int size();

private:
	std::vector<Task> _taskList;
};