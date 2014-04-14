#ifndef TASKLIST_H
#define TASKLIST_H
// @author A0097277M
#pragma once

#include <vector>
#include "Exceptions.h"
#include "Task.h"

//********************************************************************************
// This class acts as the datastore for the programme storing the Task in virtual
// memory. There are 2 main tasklist vectors, the completed and uncompleted tasklist
// which will be used to store and display completed and uncompleted task.
// There are also 4 other tasklist vectors. Searched and filter will be populated
// when their commands are called. Overdue and Clash will be updated when there is
// an instance of overdue or clash.
//********************************************************************************
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
	bool deleteTaskFromUncompletedList(unsigned int& index);
	bool deleteTaskFromCompletedList(unsigned int& index);
	bool deleteTaskFromOverdueList(unsigned int&);
	bool deleteTaskFromSearchList(unsigned int index);

	int getTaskIndex(Task* task);
	int getTaskIndexInCompletedList(Task* task);
	int getTaskIndexInSearchedList(Task* task);
	void clearTask();
	void populateSearchList(std::string& keyword);
	void populateFilterList(std::string& category);
	void populateFilterList(Date* date);

	std::vector<Task*> getSearchResults();
	std::vector<Task*> getOverdueTaskList();
	std::vector<Task*> getFilterResults();
	std::vector<Task*> getCompletedTaskList();
	std::vector<Task*> getUncompletedTaskList();
	bool updateOverdueTaskList();
	bool checkNewOverdue();
	void clearCompletedTasks();
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	unsigned int undoneSize();
	unsigned int doneSize();
	unsigned int filteredSize();
	unsigned int searchedSize();
	void updateClashStatus();
	void resetClash();
	void resetSearchedTasks();
	Task* deleteEditTask();
	Task* deleteEditTaskFromSearch();
	void clearFilteredTasks();
	void clearSearchedTasks();
	void resetFilteredTasks();
	void addTaskToFilteredList(Task& task);
	Task* getFilteredTask(int index);
	std::vector<Task*> getClashedTask();
	void shiftTask(Task* task);
	bool deleteTaskFromFilterList(unsigned int index);
	Task* setFilteredTaskAsDone(unsigned int index);
	void addBoldIndex(unsigned int index);
	void resetBoldIndexList();
	std::vector<int> getBoldIndexList();
	int getTaskIndexInFilteredList(Task* task);
	Task* setSearchedTaskAsUndone(unsigned int index);
	Task* setFilteredTaskAsUndone(unsigned int index);
	void clearClashedTaskList();
	void checkClash(Task& task, Task& otherTask);
	void addClashedTask(Task& task,Task& otherTask);
	bool validIndex(unsigned int& index);
	void removeTaskAtIndex(unsigned int& index);
	void clearOverdueTaskList();
private:
	std::vector<Task*> _uncompletedTaskList;
	std::vector<Task*> _overdueTaskList;
	std::vector<Task*> _completedTaskList;
	std::vector<Task*> _searchedTaskList;
	std::vector<Task*> _filteredTaskList;
	std::vector<Task*> _clashedTask;
	int _lastTaskIndex;
	std::vector<int> _boldIndexList;
};
#endif