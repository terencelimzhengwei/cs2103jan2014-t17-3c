#pragma once

#include <vector>
#include "Task.h"

class TaskList
{
public:
	TaskList(void);
	~TaskList(void);

	void addTask(Task&);
	Task* getTask(unsigned int);
	bool deleteTask(unsigned int&);
	unsigned int getTaskIndex(Task* task);
	void clearTask();
	Task* searchTask(std::string& keyWord);
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int size();

private:
	std::vector<Task*> _taskList;
};