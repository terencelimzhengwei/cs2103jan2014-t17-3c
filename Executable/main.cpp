#include "TimeWiseLogic.h"
#include <iostream>

int main(){
	TaskList _taskList;
	Parser _parser;
	std::string commandLine = "add testing";
	Command* command;
	command = _parser.interpretCommand(commandLine);
	command->execute(_taskList);

	system("pause");
	return 0;
}