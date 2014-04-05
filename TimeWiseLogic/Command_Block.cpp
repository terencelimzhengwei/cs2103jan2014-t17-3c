#include "Command_Block.h"


Command_Block::Command_Block(void){
	_type = BLOCK;
	_taskDescription=DEFAULT_EMPTY;
	_taskPriority = DEFAULT_PRIORITY;
	_taskType = DEFAULT_TASK_TYPE;
	_category = DEFAULT_EMPTY;
	_currentScreen=NULL;
}


Command_Block::~Command_Block(void)
{
}

void Command_Block::setDescription(std::string description){
	_taskDescription=description;
}

void Command_Block::setPriority(PRIORITY priority){
	_taskPriority=priority;
}

void Command_Block::setCategory(std::string category){
	_category=category;
}

void Command_Block::setPreviousScreen(DISPLAY_TYPE* screen){
	_currentScreen=screen;
	_previousScreen=*screen;
}

void Command_Block::addSchedule(Date* startDate, Date* endDate, ClockTime* startTime, ClockTime* endTime){
	BlockSchedule schedule(startDate,endDate,startTime,endTime);
	blockTimings.push_back(schedule);
	return;
}

bool Command_Block::execute(TaskList& taskList,std::string& feedback){
	*_currentScreen=MAIN;
	Task* _addedTask=NULL;
	std::vector<Task*>* _blockedTask = new std::vector<Task*>;
	for(unsigned int i=0;i<blockTimings.size();i++){
		if(_lastCmdCalled=="undo"){
			taskList.addTask(*_addedTaskList[i]);
		}else{
			_addedTask = new Task;
			_addedTask->setDescription(_taskDescription);
			_addedTask->setPriority(_taskPriority);
			_addedTask->setCategory(_category);
			_addedTask->setSchedule(blockTimings[i].getStartDate(),blockTimings[i].getEndDate(),blockTimings[i].getStartTime(),blockTimings[i].getEndTime());
			_addedTask->setTaskType(_taskType);
			_addedTask->setBlockedTask(_blockedTask);
			_addedTask->addBlockedTask(_addedTask);
			_addedTaskList.push_back(_addedTask);
			taskList.addTask(*_addedTask);
			//feedback = "Task added! " +_addedTask->toString();
		}
	}
	_lastCmdCalled== EXECUTE;
	return true;
}

bool Command_Block::undo(TaskList& taskList, std::string& feedback){
	if (taskList.isEmpty()){
		return false;
	} else {
		for(unsigned int i=0;i<blockTimings.size();i++){
			unsigned int index = taskList.getTaskIndex(_addedTaskList[i]);
			taskList.deleteTask(index);
		}
			*_currentScreen =_previousScreen;
			_lastCmdCalled =  CMD_TYPE_STRING[UNDO];
			return true;
	}
}
