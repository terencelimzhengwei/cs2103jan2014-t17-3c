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
	}
	return;
}

std::vector<Task*> TaskList::getSearchResults(){
	return _searchedTaskList;
}

bool TaskList::updateOverdueTaskList(){
	_overdueTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkOverdue()){
			_overdueTaskList.push_back(_taskList[i]);
			return true;
		}
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

std::vector<Task*> TaskList::getOverdueTaskList(){
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
		if(!task.checkLater(_completedTaskList[i])){
			_completedTaskList.insert(_completedTaskList.begin()+i,&task);
			return;
		}
	} 
	_completedTaskList.push_back(&task);

}

Task* TaskList::setTaskAsDone(unsigned int index){
	Task* task;
	task=_taskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTask(index);
	return task;
}

Task* TaskList::setTaskAsUndone(unsigned int index){
	Task* task;
	task=_completedTaskList[index];
	task->setStatusasUndone();
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

void TaskList::populateFilterList(std::string& keyword,SEARCH_TYPE searchType){
	_filteredTaskList.clear();

	if(searchType==CATEGORY){
		for(int i=0;i<_taskList.size();i++){
			if(_taskList[i]->hasCategory(keyword)){
				_filteredTaskList.push_back(_taskList[i]);
			}
		}
	}
	return;
}

void TaskList::populateFilterList(Date* date,SEARCH_TYPE searchType){
	_filteredTaskList.clear();

	if(searchType==DATE){
		for(int i=0;i<_taskList.size();i++){
			if(_taskList[i]->hasDate(date)){
				_filteredTaskList.push_back(_taskList[i]);
			}
		}
	}
	return;
}

void TaskList::populateFilterList(PRIORITY priority){
	_filteredTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasPriority(priority)){
			_filteredTaskList.push_back(_taskList[i]);
		}
	}
}

void TaskList::populateFilterList(TASK_STATUS status){
	_filteredTaskList.clear();

	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasStatus(status)){
			_filteredTaskList.push_back(_taskList[i]);
		}
	}
}

std::vector<Task*> TaskList::getFilterResults(){
	return _filteredTaskList;
}

void TaskList::deleteSearchedTasks(){
	for(int i=0;i<_taskList.size();i++){
		for(int j=0;j<_searchedTaskList.size();j++){
			if(_taskList[i]==_searchedTaskList[j]){
				_taskList.erase(_taskList.begin()+i);
				_searchedTaskList.erase(_searchedTaskList.begin()+j);
			}
		}
	}
}

bool TaskList::deleteTaskFromOverdueList(unsigned int& index){
	Task* task=_overdueTaskList[index];
	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]==task){
			_taskList.erase(_taskList.begin()+index);
		}
	}
	_overdueTaskList.erase(_overdueTaskList.begin()+index);
	return true;
}

bool TaskList::deleteTaskFromSearchList(unsigned int& index){
	Task* task=_searchedTaskList[index];
	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]==task){
			_taskList.erase(_taskList.begin()+index);
		}
	}
	_searchedTaskList.erase(_searchedTaskList.begin()+index);
	return true;
}

Task* TaskList::getSearchedTask(unsigned int index){
	return _searchedTaskList[index];
}

Task* TaskList::getOverdueTask(unsigned int index){
	return _overdueTaskList[index];
}

std::vector<Task*> TaskList::getCompletedTaskList(){
	return _completedTaskList;
}

std::vector<Task*> TaskList::getUncompletedTaskList(){
	return _taskList;
}

Task* TaskList::setOverdueTaskAsDone(unsigned int index){
	Task* task;
	task=_overdueTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromOverdueList(index);
	return task;
}

Task* TaskList::setSearchedTaskAsDone(unsigned int index){
	Task* task;
	task=_searchedTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromSearchList(index);
	return task;
}

void TaskList::addTaskToSearchedList(Task& task){
	for(int i=0;i<_searchedTaskList.size();i++){
		if(!task.checkLater(_taskList[i])){
			_searchedTaskList.insert(_searchedTaskList.begin()+i,&task);
			return;
		}
	} 
	_searchedTaskList.push_back(&task);
}

bool TaskList::checkNewOverdue(){
	for(int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkNewOverdue()){
			return true;
		}
	}
	return false;
}

void TaskList::addTaskToOverdueList(Task& task){
	for(int i=0;i<_overdueTaskList.size();i++){
		if(!task.checkLater(_overdueTaskList[i])){
			_overdueTaskList.insert(_overdueTaskList.begin()+i,&task);
			return;
		}
	} 
	_overdueTaskList.push_back(&task);
}
