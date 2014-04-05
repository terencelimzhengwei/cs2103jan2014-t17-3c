#include "TaskList.h"
#include <iterator>

TaskList::TaskList(void){
}


TaskList::~TaskList(void){
	_taskList.clear();
}

void TaskList::addTask(Task& task){
	_clashedTask.clear();
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->checkClash(&task)){
			if(_clashedTask.empty()){
				_clashedTask.push_back(&task);
			}
			_clashedTask.push_back(_taskList[i]);
		}
		if(!task.checkLater(_taskList[i])){
			_taskList.insert(_taskList.begin()+i,&task);
			updateClashStatus();
			return;
		}
	}  
	_taskList.push_back(&task);
	updateClashStatus();
}

bool TaskList::deleteTask(unsigned int& index)
{
	//assert(index>=0);
	//assert(index<_taskList.size());
	if(index < _taskList.size()) {
		if(_taskList[index]->getBlockedStatus()){
			_taskList[index]->removeBlock();
		}
		_taskList.erase(_taskList.begin() + index);
		updateClashStatus();
		return true;
	} else {
		throw OutOfRangeException();
		return false;
	}
}

Task* TaskList::getTask(unsigned int index)
{
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

void TaskList::populateSearchList(std::string& keyword)
{
	_searchedTaskList.clear();
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasKeyword(keyword)){
			_searchedTaskList.push_back(_taskList[i]);
		}
	}
	for(unsigned int i = 0;i<_completedTaskList.size();i++){
		if(_completedTaskList[i]->hasKeyword(keyword)){
			_searchedTaskList.push_back(_completedTaskList[i]);
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

void TaskList::addTaskToDoneList(Task& task){
	for(unsigned int i=0;i<_completedTaskList.size();i++){
		if(!task.checkLater(_completedTaskList[i])){
			_completedTaskList.insert(_completedTaskList.begin()+i,&task);
			return;
		}
	} 
	_completedTaskList.push_back(&task);

}

Task* TaskList::setTaskAsDone(unsigned int index)
{
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

Task* TaskList::setTaskAsUndone(unsigned int index)
{
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

bool TaskList::deleteTaskFromCompletedList(unsigned int& index)
{
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

Task* TaskList::getCompletedTask(unsigned int index)
{
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

int TaskList::filteredSize(){
	return _filteredTaskList.size();
}
int TaskList::searchedSize(){
	return _searchedTaskList.size();

}
void TaskList::populateFilterList(std::string& category){
	_filteredTaskList.clear();
	for(unsigned int i = 0;i<_taskList.size();i++){
		if(_taskList[i]->hasCategory(category)){
			_filteredTaskList.push_back(_taskList[i]);
		}
	}
	return;
}

void TaskList::populateFilterList(Date* date){
	_filteredTaskList.clear();

	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]->hasDate(date)){
			_filteredTaskList.push_back(_taskList[i]);
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

std::vector<Task*> TaskList::getFilterResults(){
	return _filteredTaskList;
}

void TaskList::deleteSearchedTasks(){
	while(!_searchedTaskList.empty()){
		for(unsigned int i=0;i<_taskList.size();i++){
			if(_taskList[i]==_searchedTaskList.back()){
				_taskList.erase(_taskList.begin()+i);
				_searchedTaskList.pop_back();
			}
		}
	}
}

void TaskList::deleteFilteredTasks(){
	while(!_filteredTaskList.empty()){
		for(unsigned int i=0;i<_taskList.size();i++){
			if(_taskList[i]==_filteredTaskList.back()){
				_taskList.erase(_taskList.begin()+i);
				_filteredTaskList.pop_back();
			}
		}
	}
}

bool TaskList::deleteTaskFromOverdueList(unsigned int& index)
{
	if (index < _overdueTaskList.size()) {
		Task* task=_overdueTaskList[index];
		unsigned int deletionIndex;
		for(unsigned int i=0;i<_taskList.size();i++){
			if(_taskList[i]==task){
				deletionIndex=i;
				break;
			}
		}
		deleteTask(deletionIndex);
		_overdueTaskList.erase(_overdueTaskList.begin()+index);
		return true;
	} else {
		throw OutOfRangeException();
		return false;
	}
}

bool TaskList::deleteTaskFromSearchList(unsigned int& index)
{
	Task* task=_searchedTaskList[index];
	unsigned int deletionIndex;
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]==task){
			deletionIndex=i;
			break;
		}
	}
	deleteTask(deletionIndex);
	_searchedTaskList.erase(_searchedTaskList.begin()+index);
	return true;
}

bool TaskList::deleteTaskFromFilterList(unsigned int& index)
{
	Task* task=_filteredTaskList[index];
	unsigned int deletionIndex;
	for(unsigned int i=0;i<_taskList.size();i++){
		if(_taskList[i]==task){
			deletionIndex=i;
			break;
		}
	}
	deleteTask(deletionIndex);
	_filteredTaskList.erase(_filteredTaskList.begin()+index);
	return true;
}

Task* TaskList::getSearchedTask(int index){
	return _searchedTaskList[index];
}

Task* TaskList::getFilteredTask(int index){
	return _filteredTaskList[index];
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

Task* TaskList::setOverdueTaskAsDone(unsigned int index)
{
	Task* task;
	task=_overdueTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromOverdueList(index);
	return task;
}

Task* TaskList::setSearchedTaskAsDone(unsigned int index)
{
	Task* task;
	task=_searchedTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromSearchList(index);
	return task;
}

Task* TaskList::setFilteredTaskAsDone(unsigned int index)
{
	Task* task;
	task=_filteredTaskList[index];
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	deleteTaskFromFilterList(index);
	return task;
}

void TaskList::addTaskToSearchedList(Task& task){
	for(unsigned int i=0;i<_searchedTaskList.size();i++){
		if(!task.checkLater(_searchedTaskList[i])){
			_searchedTaskList.insert(_searchedTaskList.begin()+i,&task);
			return;
		}
	} 
	_searchedTaskList.push_back(&task);
}

void TaskList::addTaskToFilteredList(Task& task){
	for(unsigned int i=0;i<_filteredTaskList.size();i++){
		if(!task.checkLater(_filteredTaskList[i])){
			_filteredTaskList.insert(_filteredTaskList.begin()+i,&task);
			return;
		}
	} 
	_filteredTaskList.push_back(&task);
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


int TaskList::getTaskIndexInSearchedList(Task* task){
	assert(task!=NULL);
	for(unsigned int i=0;i<_searchedTaskList.size();i++){
		if(task==_searchedTaskList[i]){
			return i;
		}
	}
	return DEFAULT_INDEX;
}

void TaskList::clearSearchedTasks()
{
	_searchedTaskList.clear();
}

void TaskList::clearFilteredTasks()
{
	_filteredTaskList.clear();
}
void TaskList::resetClash(){
	for(unsigned int i=0;i<_taskList.size();i++){
		_taskList[i]->resetClash();
	}
}

void TaskList::updateClashStatus()
{
	if(_taskList.empty()){
		return;
	}
	resetClash();
	for(unsigned int i=0;i<_taskList.size();i++){
		for(unsigned int j=i+1;j<_taskList.size();j++){
			if(_taskList[i]->checkClash(_taskList[j])){
				_taskList[i]->setClash(true);
				_taskList[j]->setClash(true);
			}
		}
	}
}

std::vector<Task*> TaskList::getClashedTask(){
	return _clashedTask;
}

void TaskList::shiftTask(Task* task){
	unsigned int index = getTaskIndex(task);
	deleteTask(index);
	addTask(*task);
}

unsigned int TaskList::getLastTaskIndex(){
	return _lastTaskIndex;
}

void TaskList::setLastTaskIndex(unsigned int index){
	_lastTaskIndex=index;
}
