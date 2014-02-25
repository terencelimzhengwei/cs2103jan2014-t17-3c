
#include "TimeWiseLogic.h"


TimeWiseLogic::TimeWiseLogic(void)
{
}


TimeWiseLogic::~TimeWiseLogic(void)
{
}

std::string TimeWiseLogic::processCommand(std::string commandLine){
	if(!parseCommand(commandLine)){
		return "ERROR";
	}
	else{
		//_commandProcessor.executeCommand(_cmd,_feedback);
		return "SUCCESSFUL";
	}

}

bool TimeWiseLogic::parseCommand(std::string commandLine){
	//_cmd = _parser.interpretCommand(commandLine);
	return true;
}