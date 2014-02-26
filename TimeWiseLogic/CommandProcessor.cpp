#include "CommandProcessor.h"
#include <string>
CommandProcessor::CommandProcessor(void)
{
}


CommandProcessor::~CommandProcessor(void)
{
}

void CommandProcessor::executeCommand(Command cmd) {
	Task newTask = formTask(cmd);
	_list.addTask(newTask);
}

Task CommandProcessor::formTask(Command cmd) {
	Task temp;
	std::string taskDescription = cmd.getDescription();
	temp.addDescription(taskDescription);
	return temp;
}



