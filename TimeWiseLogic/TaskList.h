#pragma once

#include <vector>
#include "Task.h"
#include "Exceptions.h"

class TaskList
{
public:
	TaskList(void);
	~TaskList(void);

	void addTask(Task&);
	void addTaskToDoneList(Task&);
	void addTaskToSearchedList(Task&);
	void addTaskToOverdueList(Task&);
	Task* setTaskAsDone(unsigned int index);
	Task* setTaskAsUndone(unsigned int index);
	Task* getTask(unsigned int index);
	Task* setOverdueTaskAsDone(unsigned int index);
	Task* setSearchedTaskAsDone(unsigned int index);
	Task* getCompletedTask(unsigned int index);
	Task* getSearchedTask(int);
	Task* getOverdueTask(int);
	bool deleteTask(unsigned int& index);
	bool deleteTaskFromCompletedList(unsigned int& index);
	bool deleteTaskFromOverdueList(unsigned int&);
	bool deleteTaskFromSearchList(unsigned int& index);

	int getTaskIndex(Task* task);
	int getTaskIndexInCompletedList(Task* task);
	int getTaskIndexInSearchedList(Task* task);
	void clearTask();
	Task* getTaskWithKeyword(std::string& keyWord);
	void populateSearchList(std::string& keyword);
	void populateFilterList(std::string& category);
	void populateFilterList(Date* date);
	void populateFilterList(PRIORITY priority);

	std::vector<Task*> getSearchResults();
	std::vector<Task*> getOverdueTaskList();
	std::vector<Task*> getFilterResults();
	std::vector<Task*> getCompletedTaskList();
	std::vector<Task*> getUncompletedTaskList();
	void updateCompletedTaskList();
	bool updateOverdueTaskList();
	bool checkNewOverdue();
	void clearCompletedTasks();
	void deleteOverdueTaskList();
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int undoneSize();
	int doneSize();
	int filteredSize();
	int searchedSize();
	void updateClashStatus();
	void resetClash();
	void deleteSearchedTasks();
	Task* deleteEditTask();
	Task* deleteEditTaskFromSearch();
	void deleteFilteredTasks();
	void clearSearchedTasks();
	void clearFilteredTasks();
	void addTaskToFilteredList(Task& task);
	Task* getFilteredTask(int index);
	std::vector<Task*> getClashedTask();
	void shiftTask(Task* task);
	bool deleteTaskFromFilterList(unsigned int& index);
	Task* setFilteredTaskAsDone(unsigned int index);
	unsigned int getLastTaskIndex();
	void setLastTaskIndex(unsigned int index);
private:
	std::vector<Task*> _taskList;
	std::vector<Task*> _overdueTaskList;
	std::vector<Task*> _completedTaskList;
	std::vector<Task*> _searchedTaskList;
	std::vector<Task*> _filteredTaskList;
	std::vector<Task*> _clashedTask;
	unsigned int _lastTaskIndex;
};