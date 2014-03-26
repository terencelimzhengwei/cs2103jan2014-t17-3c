#pragma once

#include <vector>
#include "Task.h"
#include "Clash.h"
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
	Task* setTaskAsDone(int);
	Task* setTaskAsUndone(int);
	Task* getTask(int);
	Task* setOverdueTaskAsDone(int index);
	Task* setSearchedTaskAsDone(int index);
	Task* getCompletedTask(int);
	Task* getSearchedTask(int);
	Task* getOverdueTask(int);
	bool deleteTask(int&);
	bool deleteTaskFromCompletedList(int&);
	bool deleteTaskFromOverdueList(int&);
	bool deleteTaskFromSearchList(int&);

	int getTaskIndex(Task* task);
	int getTaskIndexInCompletedList(Task* task);
	int getTaskIndexInSearchedList(Task* task);
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
	bool checkNewOverdue();
	void clearCompletedTasks();
	void deleteOverdueTaskList();
	//-----CHECKER AND GETTER FUNCTIONS-------------------------------------------------------------------------------
	bool isEmpty();
	int undoneSize();
	int doneSize();
	std::vector<Clash> checkClashes(Task* task);
	void deleteSearchedTasks();
	void setEditStatus(bool value);
	bool checkEditStatus();
	std::string retrieveForMainEdit(int index);
	Task* deleteEditTask();
	Task* deleteEditTaskFromSearch();


private:
	std::vector<Task*> _taskList;
	std::vector<Task*> _overdueTaskList;
	std::vector<Task*> _completedTaskList;
	std::vector<Task*> _searchedTaskList;
	std::vector<Task*> _filteredTaskList;
	bool _editStatus;
};