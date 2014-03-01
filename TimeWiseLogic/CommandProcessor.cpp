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

void CommandProcessor::executeCommand(Command_Add cmd) {
	switch (cmd.getType()) {
	case ADD: 
		Task newTask;
		newTask=formTask(cmd);
		_list->addTask(newTask);
	}
}

Task CommandProcessor::formTask(Command_Add cmd) {
	Task temp;
	std::string taskDescription = cmd.getDescription();
	temp.setDescription(taskDescription);
	return temp;
}



