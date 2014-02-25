#pragma once

#include <vector>
#include "Task.h"

class TaskList
{
public:
	TaskList(void);
	~TaskList(void);

	void addTask(Task task);
	Task getTask(int index);
	//void deleteTask(const int& taskIndex);
	//void clearTask();
	//std::string searchTask(std::string& keyWord);
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int size();

private:
	std::vector<Task> _taskList;
};