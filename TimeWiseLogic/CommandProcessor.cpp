#include "CommandProcessor.h"
#include <string>
CommandProcessor::CommandProcessor(void){
	_list=NULL;
}


CommandProcessor::~CommandProcessor(void){
}

void CommandProcessor::setTaskList(TaskList& taskList){
	_list=&taskList;
}

void CommandProcessor::executeCommand(Command cmd) {
	switch (cmd.getType()) {
	case ADD: 
		Task newTask;
		newTask=formTask(cmd);
		_list->addTask(newTask);
	}
}

Task CommandProcessor::formTask(Command cmd) {
	Task temp;
	std::string taskDescription = cmd.getDescription();
	temp.addDescription(taskDescription);
	return temp;
}



