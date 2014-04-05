
#include "TimeWiseLogic.h"


TimeWiseLogic::TimeWiseLogic(void){
	_manager = new CommandManager(_taskList);
	_displayType=MAIN;
	_cmd = NULL;
	initLogic();
}


TimeWiseLogic::~TimeWiseLogic(void)
{
}

std::string TimeWiseLogic::processCommand(std::string commandLine){
	if (commandLine == DEFAULT_EMPTY) {
		return NO_COMMAND_LINE;
	} else {
		if(!parseCommand(commandLine)){
		return _creator.getFeedback();
	    } else {
			try {
			std::string feedback;
			_manager->DoCommand(_cmd, feedback);
			_storage.saveFile(_taskList);
			return feedback;
		} catch (OutOfRangeException& oore) {
			delete _cmd;
			_cmd = NULL;
			return oore.what();
		} catch (UnableToEditCompletedTasks& uect) {
			delete _cmd;
			_cmd = NULL;
			return uect.what();
		} catch (UnableTosetAsDone& usad) {
			delete _cmd;
			_cmd = NULL;
			return usad.what();
		} catch (UnableToUndoneUncompletedTasks&  uuuct) {
			delete _cmd;
			_cmd = NULL;
			return uuuct.what();
		} catch (InvalidDateTimeFormatException& idtfe){
			delete _cmd;
			_cmd = NULL;
			return idtfe.what();
		} catch (InvalidStartEndDateTime& isedt) {
			delete _cmd;
			_cmd = NULL;
			return isedt.what();
		}
	}

}
}

bool TimeWiseLogic::parseCommand(std::string commandLine){
	try{
		_cmd = _creator.interpretCommand(commandLine,_displayType,_userInput,_taskList);
	}catch(...){
		return false;
	}
	return true;
}

TaskList TimeWiseLogic::getTaskList()
{
	return _taskList;
}

void TimeWiseLogic::initLogic(){
	_storage.retrieveFile(_taskList);
	_taskList.updateOverdueTaskList();
}

DISPLAY_TYPE TimeWiseLogic::setScreenToDisplay(Command* cmd){
	switch(cmd->getType()){
	case ADD:
		_displayType = MAIN;
	case BLOCK:
		_displayType=MAIN;
	default:
		return _displayType;
	}
}

DISPLAY_TYPE TimeWiseLogic::getScreenToDisplay(){
	return _displayType;
}

std::string TimeWiseLogic::getUserInput(){
	return _userInput;
}

void TimeWiseLogic::changeDisplay(DISPLAY_TYPE type){
	_displayType=type;
}
