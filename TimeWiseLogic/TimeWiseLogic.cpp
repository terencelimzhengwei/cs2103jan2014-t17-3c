
#include "TimeWiseLogic.h"


TimeWiseLogic::TimeWiseLogic(void){
	_manager = new CommandManager(_taskList);
}


TimeWiseLogic::~TimeWiseLogic(void)
{
}

std::string TimeWiseLogic::processCommand(std::string commandLine){
	if(!parseCommand(commandLine)){
		return "ERROR";
	}
	else{
			_manager->DoCommand(_cmd);
			_storage.saveFile(_taskList);
			return "SUCCESS";
	}

}

bool TimeWiseLogic::parseCommand(std::string commandLine){
	_cmd = _parser.interpretCommand(commandLine);
	return true;
}

TaskList TimeWiseLogic::getTaskList()
{
	return _taskList;
}
