#include "TaskList.h"


TaskList::TaskList(void)
{
}


TaskList::~TaskList(void)
{
}

void TaskList::addTask(Task task){
	_taskList.push_back(task);
}

Task TaskList::getTask(int index){
	return _taskList[index];
}

bool TaskList::isEmpty(){
	return _taskList.size()==0;
}

int TaskList::size(){
	return _taskList.size();
}