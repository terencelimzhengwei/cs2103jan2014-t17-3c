#pragma once

#include <vector>
#include "Task.h"
#include "Clash.h"

class TaskList
{
public:
	TaskList(void);
	~TaskList(void);

	void addTask(Task&);
	void addTaskToDoneList(Task&);
	void addTaskToSearchedList(Task&);
	Task* setTaskAsDone(unsigned int index);
	Task* setTaskAsUndone(unsigned int index);
	Task* getTask(unsigned int);
	Task* setOverdueTaskAsDone(unsigned int index);
	Task* setSearchedTaskAsDone(unsigned int index);
	Task* getCompletedTask(unsigned int);
	Task* getSearchedTask(unsigned int);
	Task* getOverdueTask(unsigned int);
	bool deleteTask(unsigned int&);
	bool deleteTaskFromCompletedList(unsigned int&);
	bool deleteTaskFromOverdueList(unsigned int&);
	bool deleteTaskFromSearchList(unsigned int&);

	unsigned int getTaskIndex(Task* task);
	unsigned int getTaskIndexInCompletedList(Task* task);
	void clearTask();
	Task* getTaskWithKeyword(std::string& keyWord);
	void populateSearchList(std::string& keyword,SEARCH_TYPE searchType);
	void populateFilterList(std::string& keyword,SEARCH_TYPE searchType);
	void populateFilterList(Date* date,SEARCH_TYPE searchType);
	void populateFilterList(PRIORITY priority);
	void populateFilterList(TASK_STATUS status);

	std::vector<Task*> getSearchResults();
	std::vector<Task*> getOverdueTaskList();
	std::vector<Task*> getFilterResults();
	std::vector<Task*> getCompletedTaskList();
	std::vector<Task*> getUncompletedTaskList();
	void updateCompletedTaskList();
	bool updateOverdueTaskList();
	void clearCompletedTasks();
	void deleteOverdueTaskList();
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int undoneSize();
	int doneSize();
	std::vector<Clash> checkClashes(Task* task);
	void deleteSearchedTasks();

private:
	std::vector<Task*> _taskList;
	std::vector<Task*> _overdueTaskList;
	std::vector<Task*> _completedTaskList;
	std::vector<Task*> _searchedTaskList;
	std::vector<Task*> _filteredTaskList;
};