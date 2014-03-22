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
	Task* getTaskWithKeyword(std::string& keyWord);
	void populateSearchList(std::string& keyword,SEARCH_TYPE searchType);
	void populateSearchList(Date* date,SEARCH_TYPE searchType);
	void populateSearchList(PRIORITY priority);
	void populateSearchList(TASK_STATUS status);

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