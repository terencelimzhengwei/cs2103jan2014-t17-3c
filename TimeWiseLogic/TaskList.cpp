#include "TaskList.h"
#include <iterator>

TaskList::TaskList(void){
}


TaskList::~TaskList(void){
	for(int i=0;i<size();i++){
		delete _taskList[i];
		_taskList[i]=NULL;
	}
}

void TaskList::addTask(Task& task){
	_taskList.push_back(&task);
}

bool TaskList::deleteTask(unsigned int& index) {
	_taskList.erase(_taskList.begin() + index);
	return true;
}

Task* TaskList::getTask(unsigned int index)
{
	return _taskList[index];
}

bool TaskList::isEmpty(){
	return _taskList.size()==0;
}

int TaskList::size(){
	return _taskList.size();
}

unsigned int TaskList::getTaskIndex(Task* task){
	for(int i=0;i<_taskList.size();i++){
		if(task==getTask(i)){
			return i;
		}
	}
	return DEFAULT_INDEX;
}

void TaskList::clearTask(){
	_taskList.clear();
}

Task* TaskList::searchTask(std::string& keyWord){
	for(int i=0;i<size();i++){
		if(_taskList[i]->hasKeyword(keyWord)){
			return _taskList[i];
		}
	}
	return NULL;
}

void TaskList::getTasksWithKeyword(std::string& keyword){
	_searchedTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasKeyword(keyword)){
			_searchedTaskList.push_back(_taskList[i]);
		}
	}
}

std::vector<Task*> TaskList::getSearchResults()
{
	return _searchedTaskList;
}

void TaskList::updateOverdueTaskList(){
	_overdueTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkOverdue()){
			_overdueTaskList.push_back(_taskList[i]);
		}
	}
}

void TaskList::deleteCompletedTaskList(){
	for(int i=0;i<_taskList.size();i++){
		for(int j=0;j<_completedTaskList.size();j++){
			if(_taskList[i]==_completedTaskList[j]){
				_taskList.erase(_taskList.begin()+i);
				_completedTaskList.erase(_completedTaskList.begin()+j);
			}
		}
	}
}

void TaskList::deleteOverdueTaskList(){
	for(int i=0;i<_taskList.size();i++){
		for(int j=0;j<_overdueTaskList.size();j++){
			if(_taskList[i]==_overdueTaskList[j]){
				_taskList.erase(_taskList.begin()+i);
				_overdueTaskList.erase(_overdueTaskList.begin()+j);
			}
		}
	}
}

void TaskList::updateCompletedTaskList(){
	_completedTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->getTaskStatus()==COMPLETED){
			_completedTaskList.push_back(_taskList[i]);
		}
	}
}
