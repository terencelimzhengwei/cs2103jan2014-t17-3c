#include "TaskList.h"
#include <iterator>

TaskList::TaskList(void){
}


TaskList::~TaskList(void){
	_taskList.clear();
}

void TaskList::addTask(Task& task){
	for(int i=0;i<_taskList.size();i++){
		if(!task.checkLater(_taskList[i])){
			_taskList.insert(_taskList.begin()+i,&task);
			return;
		}
	}  
	_taskList.push_back(&task);
}

bool TaskList::deleteTask(unsigned int& index) {
	assert(index>=0);
	assert(index<_taskList.size());
	_taskList.erase(_taskList.begin() + index);
	return true;
}

Task* TaskList::getTask(unsigned int index){
	return _taskList[index];
}

bool TaskList::isEmpty(){
	return _taskList.size()==0;
}

int TaskList::undoneSize(){
	return _taskList.size();
}

unsigned int TaskList::getTaskIndex(Task* task){
	assert(task!=NULL);
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

Task* TaskList::getTaskWithKeyword(std::string& keyWord){
	for(int i=0;i<undoneSize();i++){
		if(_taskList[i]->hasKeyword(keyWord)){
			return _taskList[i];
		}
	}
	return NULL;
}

void TaskList::populateSearchList(std::string& keyword,SEARCH_TYPE searchType){
	_searchedTaskList.clear();

	if(searchType==KEYWORD){
		for(int i=0;i<_taskList.size();i++){
			if(_taskList[i]->hasKeyword(keyword)){
				_searchedTaskList.push_back(_taskList[i]);
			}
		}
	}else if(searchType==CATEGORY){
		for(int i=0;i<_taskList.size();i++){
			if(_taskList[i]->hasCategory(keyword)){
				_searchedTaskList.push_back(_taskList[i]);
			}
		}
	}
	return;
}

void TaskList::populateSearchList(Date* date,SEARCH_TYPE searchType){
	_searchedTaskList.clear();

	if(searchType==DATE){
		for(int i=0;i<_taskList.size();i++){
			if(_taskList[i]->hasDate(date)){
				_searchedTaskList.push_back(_taskList[i]);
			}
		}
	}
	return;
}

void TaskList::populateSearchList(PRIORITY priority){
	_searchedTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasPriority(priority)){
			_searchedTaskList.push_back(_taskList[i]);
		}
	}
}

void TaskList::populateSearchList(TASK_STATUS status){
	_searchedTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasStatus(status)){
			_searchedTaskList.push_back(_taskList[i]);
		}
	}
}

std::vector<Task*> TaskList::getSearchResults(){
	return _searchedTaskList;
}

bool TaskList::updateOverdueTaskList(){
	int previousSize=_overdueTaskList.size();
	_overdueTaskList.clear();
	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkOverdue()){
			_overdueTaskList.push_back(_taskList[i]);
		}
	}
	if(_overdueTaskList.size()!=previousSize){
		return true;
	}
	return false;
}

void TaskList::clearCompletedTasks(){
	_completedTaskList.clear();
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

std::vector<Task*> TaskList::getOverdueTasks(){
	return _overdueTaskList;
}

std::vector<Clash> TaskList::checkClashes(Task* task){
	std::vector<Clash> clashList;
	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkClash(task)){
			Clash clashes(_taskList[i],task);
			clashList.push_back(clashes);
		}
	}
	return clashList;
}

void TaskList::addTaskToDoneList(Task& task){
	for(int i=0;i<_completedTaskList.size();i++){
		if(!task.checkLater(_taskList[i])){
			_completedTaskList.insert(_completedTaskList.begin()+i,&task);
			return;
		}
	} 
	_completedTaskList.push_back(&task);

}

Task* TaskList::setTaskAsDone(unsigned int index){
	Task* task;
	task=_taskList[index];
	addTaskToDoneList(*task);
	deleteTask(index);
	return task;
}

Task* TaskList::setTaskAsUndone(unsigned int index){
	Task* task;
	task=_completedTaskList[index];
	addTask(*task);
	deleteTaskFromCompletedList(index);
	return task;
}

bool TaskList::deleteTaskFromCompletedList(unsigned int& index){
	_completedTaskList.erase(_completedTaskList.begin() + index);
	return true;
}

unsigned int TaskList::getTaskIndexInCompletedList(Task* task){
	assert(task!=NULL);
	for(int i=0;i<_completedTaskList.size();i++){
		if(task==_completedTaskList[i]){
			return i;
		}
	}
	return DEFAULT_INDEX;
}

Task* TaskList::getCompletedTask(unsigned int index){
	return _completedTaskList[index];
}

int TaskList::doneSize(){
	return _completedTaskList.size();
}
