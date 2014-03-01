#include "Command.h"

const CMD_TYPE Command::DEFAULT_COMMAND_TYPE = UNDEFINED;
const int Command::DEFAULT_TASK_INDEX = -1;
const PRIORITY Command::DEFAULT_PRIORITY = LOW;
const TASK_STATUS Command::DEFAULT_TASK_STATUS = UNCOMPLETED;
const TASK_TYPE Command::DEFAULT_TASK_TYPE = FLOATING;
const std::string Command::DEFAULT_CATEGORY = "Undefined";

Command::Command(void){
}


Command::~Command(void){
}

void Command::init() {
	_type = DEFAULT_COMMAND_TYPE;
	_taskIndex = DEFAULT_TASK_INDEX;
	_taskPriority = DEFAULT_PRIORITY;
	_taskType = DEFAULT_TASK_TYPE;
	_taskStatus = DEFAULT_TASK_STATUS;
	_category = DEFAULT_CATEGORY;
}

	