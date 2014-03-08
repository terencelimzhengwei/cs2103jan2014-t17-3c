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

bool TaskList::deleteTask(unsigned int& userIdx) {
	unsigned int index = userIdx - 1; 
	if(_taskList.empty()) {
		return false;
		//exception
	}
	else if(index < 0 || index > _taskList.size() - 1) {
		return false;
	} else {
		_taskList.erase(_taskList.begin() + index);
		return true;
	}
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
}
