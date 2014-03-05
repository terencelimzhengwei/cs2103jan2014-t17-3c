#include "TaskList.h"
#include <iterator>

TaskList::TaskList(void)
{
}


TaskList::~TaskList(void)
{
}

void TaskList::addTask(Task task){
	_taskList.push_back(task);
}

void TaskList::addTask(unsigned int taskIndex, Task task) {
	std::vector<Task>:: iterator it;
	it = _taskList.begin();

	for (int i = 1; i < taskIndex; i++) {
		it++;
	}
	_taskList.insert(it,task);
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
Task TaskList::getTask(unsigned int index){
	return _taskList[index];
}

bool TaskList::isEmpty(){
	return _taskList.size()==0;
}

int TaskList::size(){
	return _taskList.size();
}