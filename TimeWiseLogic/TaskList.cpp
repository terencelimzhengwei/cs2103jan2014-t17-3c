#include "TaskList.h"
#include <iterator>

TaskList::TaskList(void){
	_editStatus=false;
}


TaskList::~TaskList(void){
	_taskList.clear();
}

void TaskList::addTask(Task& task){
	for(unsigned int i=0;i<_taskList.size();i++){
		if(!task.checkLater(_taskList[i])){
			_taskList.insert(_taskList.begin()+i,&task);
			return;
		}
	}  
	_taskList.push_back(&task);
}

bool TaskList::deleteTask(int& index) {
	//assert(index>=0);
	//assert(index<_taskList.size());
	if(index < _taskList.size()) {
	_taskList.erase(_taskList.begin() + index);
	return true;
	} else {
		throw OutOfRangeException();
		return false;
	}
}

Task* TaskList::getTask(int index){
	if (index <_taskList.size()) {

	return _taskList[index];
	} else {
		throw OutOfRangeException();
		return NULL;
	}
}

bool TaskList::isEmpty(){
	return _taskList.size()==0;
}

int TaskList::undoneSize(){
	return _taskList.size();
}

int TaskList::getTaskIndex(Task* task){
	assert(task!=NULL);
	for(unsigned int i=0;i<_taskList.size();i++){
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

	if(searchType == KEYWORD){
		for(unsigned int i=0;i<_taskList.size();i++){
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

	for(unsigned int i=0;i<_taskList.size();i++){
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
	for(unsigned int i=0;i<_taskList.size();i++){
		for(unsigned int j=0;j<_overdueTaskList.size();j++){
			if(_taskList[i]==_overdueTaskList[j]){
				_taskList.erase(_taskList.begin()+i);
				_overdueTaskList.erase(_overdueTaskList.begin()+j);
			}
		}
	}
}

void TaskList::updateCompletedTaskList(){
	_completedTaskList.clear();

	for(unsigned int i=0;i<_taskList.size();i++){
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
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkClash(task)){
			Clash clashes(_taskList[i],task);
			clashList.push_back(clashes);
		}
	}
	return clashList;
}

void TaskList::addTaskToDoneList(Task& task){
	for(unsigned int i=0;i<_completedTaskList.size();i++){
		if(!task.checkLater(_completedTaskList[i])){
			_completedTaskList.insert(_completedTaskList.begin()+i,&task);
			return;
		}
	} 
	_completedTaskList.push_back(&task);

}

Task* TaskList::setTaskAsDone(int index){
	if (index < _taskList.size()) {
	Task* task;
	task=_taskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTask(index);
	return task;
	} else {
		throw OutOfRangeException();
		return NULL;
	}
}

Task* TaskList::setTaskAsUndone(int index) {
	if(index <_completedTaskList.size()) {
	Task* task;
	task=_completedTaskList[index];
	task->setStatusasUndone();
	addTask(*task);
	deleteTaskFromCompletedList(index);
	return task;
	} else {
		throw OutOfRangeException();
		return NULL;
	}
}

bool TaskList::deleteTaskFromCompletedList(int& index){
	if (index <_completedTaskList.size()) {
	_completedTaskList.erase(_completedTaskList.begin() + index);
	return true;
	} else {
		throw OutOfRangeException();
		return false;
	}
}

int TaskList::getTaskIndexInCompletedList(Task* task){
	assert(task!=NULL);
	for(unsigned int i=0;i<_completedTaskList.size();i++){
		if(task==_completedTaskList[i]){
			return i;
		}
	}
	return DEFAULT_INDEX;
}

Task* TaskList::getCompletedTask(int index){
	if(index < _completedTaskList.size()) {
	return _completedTaskList[index];
	}
	else {
		throw OutOfRangeException();
		return NULL;
	}
}

int TaskList::doneSize(){
	return _completedTaskList.size();
}

void TaskList::populateFilterList(std::string& keyword,SEARCH_TYPE searchType){
	_filteredTaskList.clear();

	if(searchType==CATEGORY){
		for(unsigned int i=0;i<_taskList.size();i++){
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
		for(unsigned int i=0;i<_taskList.size();i++){
			if(_taskList[i]->hasDate(date)){
				_filteredTaskList.push_back(_taskList[i]);
			}
		}
	}
	return;
}

void TaskList::populateFilterList(PRIORITY priority){
	_filteredTaskList.clear();

	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasPriority(priority)){
			_filteredTaskList.push_back(_taskList[i]);
		}
	}
}

void TaskList::populateFilterList(TASK_STATUS status){
	_filteredTaskList.clear();

	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasStatus(status)){
			_filteredTaskList.push_back(_taskList[i]);
		}
	}
}

std::vector<Task*> TaskList::getFilterResults(){
	return _filteredTaskList;
}

void TaskList::deleteSearchedTasks(){
	for(unsigned int i=0;i<_taskList.size();i++){
		for(unsigned int j=0;j<_searchedTaskList.size();j++){
			if(_taskList[i]==_searchedTaskList[j]){
				_taskList.erase(_taskList.begin()+i);
				_searchedTaskList.erase(_searchedTaskList.begin()+j);
			}
		}
	}
}

bool TaskList::deleteTaskFromOverdueList(int& index){
	if (index < _overdueTaskList.size()) {
	Task* task=_overdueTaskList[index];
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]==task){
			_taskList.erase(_taskList.begin()+i);
		}
	}
	_overdueTaskList.erase(_overdueTaskList.begin()+index);
	return true;
	} else {
		throw OutOfRangeException();
		return false;
	}
}

bool TaskList::deleteTaskFromSearchList(int& index){
	Task* task=_searchedTaskList[index];
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]==task){
			_taskList.erase(_taskList.begin()+i);
		}
	}
	_searchedTaskList.erase(_searchedTaskList.begin()+index);
	return true;
}

Task* TaskList::getSearchedTask(int index){
	return _searchedTaskList[index];
}

Task* TaskList::getOverdueTask(int index){
	return _overdueTaskList[index];
}

std::vector<Task*> TaskList::getCompletedTaskList(){
	return _completedTaskList;
}

std::vector<Task*> TaskList::getUncompletedTaskList(){
	return _taskList;
}

Task* TaskList::setOverdueTaskAsDone(int index){
	Task* task;
	task=_overdueTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromOverdueList(index);
	return task;
}

Task* TaskList::setSearchedTaskAsDone(int index){
	Task* task;
	task=_searchedTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromSearchList(index);
	return task;
}

void TaskList::addTaskToSearchedList(Task& task){
	for(unsigned int i=0;i<_searchedTaskList.size();i++){
		if(!task.checkLater(_taskList[i])){
			_searchedTaskList.insert(_searchedTaskList.begin()+i,&task);
			return;
		}
	} 
	_searchedTaskList.push_back(&task);
}

bool TaskList::checkNewOverdue(){
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkNewOverdue()){
			return true;
		}
	}
	return false;
}

void TaskList::addTaskToOverdueList(Task& task){
	for(unsigned int i=0;i<_overdueTaskList.size();i++){
		if(!task.checkLater(_overdueTaskList[i])){
			_overdueTaskList.insert(_overdueTaskList.begin()+i,&task);
			return;
		}
	} 
	_overdueTaskList.push_back(&task);
}

void TaskList::setEditStatus(bool value){
	_editStatus=value;
}

bool TaskList::checkEditStatus(){
	return _editStatus;
}

Task* TaskList::deleteEditTask(){
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkEditStatus()){
			Task* task = _taskList[i];
			_taskList.erase(_taskList.begin()+i);
			_editStatus=false;
			return task;
		}
	}
	return NULL;
}

Task* TaskList::deleteEditTaskFromSearch(){
	for(unsigned int i=0;i<_searchedTaskList.size();i++){
		if(_searchedTaskList[i]->checkEditStatus()){
			Task* task = _searchedTaskList[i];
			_searchedTaskList.erase(_searchedTaskList.begin()+i);
			for(int j=0;j<_taskList.size();j++){
				if(_taskList[j]==task){
					_taskList.erase(_taskList.begin()+j);
					_editStatus=false;
					return task;
				}
			}
		}
	}
	return NULL;
}

int TaskList::getTaskIndexInSearchedList(Task* task){
	assert(task!=NULL);
	for(unsigned int i=0;i<_searchedTaskList.size();i++){
		if(task==_searchedTaskList[i]){
			return i;
		}
	}
	return DEFAULT_INDEX;
}
