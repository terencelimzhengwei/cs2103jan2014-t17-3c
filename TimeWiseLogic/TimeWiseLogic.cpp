
#include "TimeWiseLogic.h"


TimeWiseLogic::TimeWiseLogic(void){
	_manager = new CommandManager(_taskList);
	_logger = Logger::getLogger();
	_displayType=MAIN;
	_cmd = NULL;
	initLogic();
}


TimeWiseLogic::~TimeWiseLogic(void)
{
}

std::string TimeWiseLogic::processCommand(std::string commandLine){
	if (emptyCommandLine(commandLine)) {
		return NO_COMMAND_LINE;
	} else {
		_taskList.resetLastTaskIndexList();

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
			} catch (UnableToSetAsDone& usad) {
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
			} catch (NoArgumentException& nae) {
				delete _cmd;
				_cmd = NULL;
				return nae.what();
			} catch (InvalidAddCommandInputException& iacie) {
				delete _cmd;
				_cmd = NULL;
				return iacie.what();
			} catch (NotANumberException& nane) {
				delete _cmd;
				_cmd = NULL;
				return nane.what();
			} catch (InvalidFilterCommandInputException& ifp) {
				delete _cmd;
				_cmd = NULL;
				return ifp.what();
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

TaskList TimeWiseLogic::getTaskList(){
	return _taskList;
}

void TimeWiseLogic::initLogic(){
	_logger->log("TimeWiseLogic","Initializing Logic");
	_storage.retrieveFile(_taskList);
	_taskList.updateOverdueTaskList();
}

DISPLAY_TYPE TimeWiseLogic::getScreenToDisplay(){
	return _displayType;
}

bool TimeWiseLogic::emptyCommandLine(std::string commandLine){
	return (commandLine==DEFAULT_EMPTY);
}