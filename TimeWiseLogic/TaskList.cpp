#include "TaskList.h"
#include <iterator>

TaskList::TaskList(void){
}


TaskList::~TaskList(void){
	_uncompletedTaskList.clear();
}

void TaskList::addTask(Task& task)
{
	clearClashedTaskList();
	for(unsigned int i = 0;i <undoneSize();i++){
		checkClash(task,*_uncompletedTaskList[i]);
		if(!task.checkLater(_uncompletedTaskList[i])){
			_uncompletedTaskList.insert(_uncompletedTaskList.begin()+i,&task);
			updateClashStatus();
			return;
		}
	}  
	_uncompletedTaskList.push_back(&task);
	updateClashStatus();
}

bool TaskList::deleteTaskFromUncompletedList(unsigned int& index){
	if(validIndex(index)){
		removeTaskAtIndex(index);
		updateClashStatus();
		return true;
	}else {
		throw OutOfRangeException();
	}
}

Task* TaskList::getTask(unsigned int index){
	if (validIndex(index)) {
		return _uncompletedTaskList[index];
	} else {
		throw OutOfRangeException();
	}
}

bool TaskList::isEmpty(){
	return (undoneSize()==ZERO);
}

unsigned int TaskList::undoneSize(){
	return _uncompletedTaskList.size();
}

int TaskList::getTaskIndex(Task* task){
	assert(task!=NULL);
	for(unsigned int i=0;i<undoneSize();i++){
		if(task==getTask(i)){
			return i;
		}
	}
	return DEFAULT_INDEX;
}

void TaskList::clearTask(){
	_uncompletedTaskList.clear();
}

void TaskList::populateSearchList(std::string& keyword){
	resetSearchedTasks();
	for(unsigned int i=0;i<undoneSize();i++){
		if(_uncompletedTaskList[i]->hasKeyword(keyword)){
			addTaskToSearchedList(*_uncompletedTaskList[i]);
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
	clearOverdueTaskList();
	bool overdue=false;
	for(unsigned int i=0;i<undoneSize();i++){
		if(_uncompletedTaskList[i]->checkOverdue()){
			addTaskToOverdueList(*_uncompletedTaskList[i]);
			overdue=true;
		}
	}
	return overdue;
}

void TaskList::clearCompletedTasks(){
	_completedTaskList.clear();
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

Task* TaskList::setTaskAsDone(unsigned int index){
	if (validIndex(index)) {
		Task* task;
		task=_uncompletedTaskList[index];
		task->setStatusAsDone();
		addTaskToDoneList(*task);
		deleteTaskFromUncompletedList(index);
		return task;
	} else {
		throw OutOfRangeException();
		return NULL;
	}
}

Task* TaskList::setTaskAsUndone(unsigned int index){
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

Task* TaskList::setSearchedTaskAsUndone(unsigned int index){
	if(index <_searchedTaskList.size()) {
		Task* task = getSearchedTask(index);
		task->setStatusasUndone();
		addTask(*task);
		unsigned int completedListIndex = getTaskIndexInCompletedList(task);
		deleteTaskFromCompletedList(completedListIndex);
		return task;
	} else {
		throw OutOfRangeException();
		return NULL;
	}
}

Task* TaskList::setFilteredTaskAsUndone(unsigned int index){
	if(index <_filteredTaskList.size()) {
		Task* task = getFilteredTask(index);
		task->setStatusasUndone();
		addTask(*task);
		unsigned int completedListIndex = getTaskIndexInCompletedList(task);
		deleteTaskFromCompletedList(completedListIndex);
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
	for(unsigned int i = 0;i<_uncompletedTaskList.size();i++){
		if(_uncompletedTaskList[i]->hasCategory(category)){
			_filteredTaskList.push_back(_uncompletedTaskList[i]);
		}
	}
	return;
}

void TaskList::populateFilterList(Date* date){
	_filteredTaskList.clear();

	for(unsigned int i=0;i<_uncompletedTaskList.size();i++){
		if(_uncompletedTaskList[i]->hasDate(date)){
			_filteredTaskList.push_back(_uncompletedTaskList[i]);
		}
	}
	return;
}

std::vector<Task*> TaskList::getFilterResults(){
	return _filteredTaskList;
}

void TaskList::clearSearchedTasks(){
	while(!_searchedTaskList.empty()){
		deleteTaskFromSearchList(0);
	}
}

void TaskList::clearFilteredTasks(){
	while(!_filteredTaskList.empty()){
		deleteTaskFromFilterList(0);
	}
}

bool TaskList::deleteTaskFromOverdueList(unsigned int& index)
{
	if (index < _overdueTaskList.size()) {
		Task* task=_overdueTaskList[index];
		unsigned int deletionIndex;
		for(unsigned int i=0;i<_uncompletedTaskList.size();i++){
			if(_uncompletedTaskList[i]==task){
				deletionIndex=i;
				break;
			}
		}
		deleteTaskFromUncompletedList(deletionIndex);
		_overdueTaskList.erase(_overdueTaskList.begin()+index);
		return true;
	} else {
		throw OutOfRangeException();
		return false;
	}
}

bool TaskList::deleteTaskFromSearchList(unsigned int index){
	Task* task=getSearchedTask(index);
	unsigned int deletionIndex;
	if(task->getTaskStatus()==COMPLETED) {
		for(unsigned int i = 0; i < doneSize();i++){
			if(_completedTaskList[i]==task){
				deletionIndex=i;
				break;
			}
		}
		deleteTaskFromCompletedList(deletionIndex);
	}else{
		for(unsigned int i=0;i<undoneSize();i++){
			if(_uncompletedTaskList[i]==task){
				deletionIndex=i;
				break;
			}
		}
		deleteTaskFromUncompletedList(deletionIndex);
	}
	_searchedTaskList.erase(_searchedTaskList.begin()+index);
	return true;
}

bool TaskList::deleteTaskFromFilterList(unsigned int index)
{
	Task* task=_filteredTaskList[index];
	unsigned int deletionIndex;
	for(unsigned int i=0;i<_uncompletedTaskList.size();i++){
		if(_uncompletedTaskList[i]==task){
			deletionIndex=i;
			break;
		}
	}
	deleteTaskFromUncompletedList(deletionIndex);
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
	return _uncompletedTaskList;
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
	if(task->getTaskStatus()==DONE){
		throw UnableToSetAsDone();
	}
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	unsigned int uncompletedIndex = getTaskIndex(task);
	deleteTaskFromUncompletedList(uncompletedIndex);
	return task;
}

Task* TaskList::setFilteredTaskAsDone(unsigned int index)
{
	Task* task;
	task=_filteredTaskList[index];
	if(task->getTaskStatus()==DONE){
		throw UnableToSetAsDone();
	}
	task->setStatusAsDone();
	addTaskToDoneList(*task);
	unsigned int uncompletedIndex = getTaskIndexInFilteredList(task);
	deleteTaskFromUncompletedList(uncompletedIndex);
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
	for(unsigned int i=0;i<_uncompletedTaskList.size();i++){
		if(_uncompletedTaskList[i]->checkNewOverdue()){
			return true;
		}
	}
	return false;
}

void TaskList::addTaskToOverdueList(Task& task){
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

int TaskList::getTaskIndexInFilteredList(Task* task){
	assert(task!=NULL);
	for(unsigned int i=0;i<_filteredTaskList.size();i++){
		if(task==_filteredTaskList[i]){
			return i;
		}
	}
	return DEFAULT_INDEX;
}

void TaskList::resetSearchedTasks(){
	_searchedTaskList.clear();
}

void TaskList::resetFilteredTasks(){
	_filteredTaskList.clear();
}
void TaskList::resetClash(){
	for(unsigned int i=0;i<_uncompletedTaskList.size();i++){
		_uncompletedTaskList[i]->resetClash();
	}
}

void TaskList::updateClashStatus()
{
	if(_uncompletedTaskList.empty()){
		return;
	}
	resetClash();
	for(unsigned int i=0;i<_uncompletedTaskList.size();i++){
		for(unsigned int j=i+1;j<_uncompletedTaskList.size();j++){
			if(_uncompletedTaskList[i]->checkClash(_uncompletedTaskList[j])){
				_uncompletedTaskList[i]->setClash(true);
				_uncompletedTaskList[j]->setClash(true);
			}
		}
	}
}

std::vector<Task*> TaskList::getClashedTask(){
	return _clashedTask;
}

void TaskList::shiftTask(Task* task){
	unsigned int index = getTaskIndex(task);
	deleteTaskFromUncompletedList(index);
	addTask(*task);
}

void TaskList::resetLastTaskIndexList(){
	_lastTaskIndexList.clear();
}

void TaskList::addLastTaskIndex(unsigned int index){
	_lastTaskIndexList.push_back(index);
}

std::vector<int> TaskList::getLastTaskIndexList(){
	return _lastTaskIndexList;
}

void TaskList::clearClashedTaskList(){
	_clashedTask.clear();
}

void TaskList::clearOverdueTaskList(){
	_overdueTaskList.clear();
}

void TaskList::addClashedTask(Task& task,Task& otherTask)
{
	if(_clashedTask.empty()){
		_clashedTask.push_back(&task);
	}
	_clashedTask.push_back(&otherTask);
}

void TaskList::checkClash(Task& task, Task& otherTask)
{
	if(task.checkClash(&otherTask)){
		addClashedTask(task,otherTask);
	}
}

bool TaskList::validIndex(unsigned int& index){
	return (index < _uncompletedTaskList.size());
}

void TaskList::removeTaskAtIndex(unsigned int& index){
	_uncompletedTaskList.erase(_uncompletedTaskList.begin() + index);
}