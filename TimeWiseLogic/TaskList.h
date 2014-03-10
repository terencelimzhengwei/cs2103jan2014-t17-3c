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
	void getTasksWithKeyword(std::string& keyword);
	std::vector<Task*> getSearchResults();
	void updateCompletedTaskList();
	void updateOverdueTaskList();
	void deleteCompletedTaskList();
	void deleteOverdueTaskList();
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int size();

private:
	std::vector<Task*> _taskList;
	std::vector<Task*> _overdueTaskList;
	std::vector<Task*> _completedTaskList;
	std::vector<Task*> _searchedTaskList;
	std::vector<std::vector<Task*>> _clashList;
};