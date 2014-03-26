#include "CommandCreator.h"


CommandCreator::CommandCreator(void)
{
}


CommandCreator::~CommandCreator(void)
{
}


void CommandCreator::flagArg(std::string input){
	if (input.length() == 0) {
		throw NoArgumentException();
	}
}

void CommandCreator::flagDescription(std::string input){
	if (input.length() == 0 ) {
		throw InvalidAddCommandInputException();
	}
}

void CommandCreator::flagIndex(unsigned int id) {
	if (id < 0 || id == 0) {
		throw OutOfRangeException();
	}
}



	//the below methods are responsible for creating the derived commands
Command* CommandCreator::interpretCommand(std::string userInput,DISPLAY_TYPE& displayType,std::string& commandLineInput)
{
	try {

		string commandTypeString = _parser.getFirstWord(userInput);
		CMD_TYPE commandType = _parser.determineCommandType(commandTypeString); 

		// Assume all other commands are adding event
		if(commandType==UNDEFINED) {
			userInput = "add " + userInput;
			commandType = ADD;
		}
	
		string parameter = _parser.removeFirstWord(userInput);
		_parser.removeWhiteSpaces(parameter);
		vector<string> parameters = _parser.splitBySpace(parameter);
		unsigned int parameterNum = parameters.size();
		switch (commandType) {
			case ADD: {
				return createCommandAdd(parameter,parameterNum,parameters,&displayType);
			}
			
			case DELETE: {
				return createCommandDelete(parameter,&displayType);
			}
			case EDIT: {
				return createCommandEdit(parameters,&displayType,&userInput);
			}
			case DONE: {
				return createCommandDone(parameter,&displayType);
			}
			case UNDONE: {
				return createCommandUndone(parameter,&displayType);
			}
			case CLEAR: {
				return createCommandClear(parameter,&displayType);
			}
			case UNDO: {
				return createCommandUndo();
			}
			case REDO: {
				return createCommandRedo();
			}
			case SEARCH: {
				return createCommandSearch(parameter,&displayType);
			}
			case DISPLAY:
				return createCommandDisplay(parameter,&displayType);
			default: {
				throw InvalidCommandWordException();
				return NULL;
			}
		}
	} catch (InvalidCommandWordException& icwe) {
		_feedbackExceptiontoUI = icwe.what();
		throw InvalidCommandWordException();
	} catch (NoArgumentException& nae) {
		_feedbackExceptiontoUI = nae.what();
		throw NoArgumentException();
	} catch (InvalidAddCommandInputException& iacie) {
		_feedbackExceptiontoUI = iacie.what();
		throw InvalidAddCommandInputException();
	} catch (OutOfRangeException& oore) {
		_feedbackExceptiontoUI = oore.what();
		throw OutOfRangeException();
	} catch (NotANumberException& nane) {
		_feedbackExceptiontoUI = nane.what();
		throw NotANumberException();
	}

}

Command* CommandCreator::createCommandAdd(std::string parameter, unsigned int parameterNum, vector<std::string> parameters,DISPLAY_TYPE* screen)
{
	std::vector<std::string> dates;
	std::vector<std::string> times;
	std::string category = "";
	std::string priority = "";
	string description = "";
	flagArg(parameter);
	//int wordReading = parameterNum - 1;
	if(_parser.isCategory(parameters.back())){
		category=_parser.replaceWord("#","",parameters.back());
		parameters.pop_back();
	}
	if(_parser.isPriority(parameters.back())){
		priority=_parser.replaceWord("!","",parameters.back());
		parameters.pop_back();
	}

	while(!parameters.empty()){
		if(_parser.isTimeFormat(parameters.back())) {
			//times.push_back(parameters.back());
			times.push_back(_parser.strval(_parser.extractTime(parameters.back(), 0)[0]));
			parameters.pop_back();
			if(parameters.size()!=0 && _parser.isPreposition(parameters.back())) {
				parameters.pop_back();
			}
		} else if(_parser.isDateFormat(parameters.back())) {
			/* } else if( _parser.isDateFormat(parameters.back()) ||
				_parser.isDateFormat(parameters[parameters.size()-2] + parameters.back()) ||
				_parser.isDateFormat(parameters[parameters.size()-3] + parameters[parameters.size()-2] + parameters.back()) ) {*/

					dates.push_back(parameters.back());
					parameters.pop_back();

					/* vector<int> dateData = _parser.extractDate(parameter, parameters.size()-1);
					for(int i=0 ; i<dateData[3] ; i++) {
						parameters.pop_back();
					}
					dates.push_back(_parser.strval(dateData[2] + dateData[1]*100 + dateData[0]*1000)); */

					if(parameters.size()!=0 && _parser.isPreposition(parameters.back())){
						parameters.pop_back();
					}
			
		} else {
			while(!parameters.empty()){
				description += parameters.front()+" ";
				parameters.erase(parameters.begin());
			}
		}

	}

	flagDescription(description);
	_parser.removeWhiteSpaces(description);

	for(int i=0;i<times.size();i++){
		times[i] = _parser.replaceWord(":","",times[i]);
	}

	Command_Add* commandAdd = new Command_Add;

	if(category!="") {
		commandAdd->setCategory(category);
	}

	if(priority!="") {
		if(priority=="H" || priority == PRIORITY_STRING[0]) {
			commandAdd->setPriority(HIGH);
		} else if(priority=="M" || priority == PRIORITY_STRING[1]) {
			commandAdd->setPriority(MEDIUM);
		} else if(priority=="L" || priority ==PRIORITY_STRING[2]) {
			commandAdd->setPriority(LOW);
		}
	}

	commandAdd->setDescription(description);

	if(!dates.empty()) {
		switch(dates.size()){
		case 1:
			commandAdd->setEndDate(*_parser.createDate(dates.back()));
			break;
		case 2:
			commandAdd->setStartDate(*_parser.createDate(dates.back()));
			dates.pop_back();
			commandAdd->setEndDate(*_parser.createDate(dates.back()));
			break;
		default:
			delete commandAdd;
			commandAdd=NULL;
			throw InvalidAddCommandInputException();
		}
	}
	if(!times.empty()) {
		if (dates.empty()) {
			switch(times.size()){
			case 1: {
				// compare the time set by users with the current time
				ClockTime* endTime = _parser.createTime(times.back());
				bool timeStatus = endTime->checkOverdueTime();
				Date toBeSet;
				// when current time is later than time set by user, set end date 
				// to tomorrow
				if(timeStatus) {
					toBeSet.setDateAsTomorrow();
					commandAdd->setEndDate(toBeSet);
				} else {
					//when current time is earlier than the time set by user, 
					//set end date to today
					int month = toBeSet.getCurrentMonth();
					int year = toBeSet.getCurrentYear();
					int day = toBeSet. getCurrentDay();
					Date today(day,month,year);
					commandAdd->setEndDate(today);
				}
				commandAdd->setEndTime(*endTime);
				break;
		  }
			case 2:{
				// compare the time set by users with the current time
				ClockTime* startTime = _parser.createTime(times.back());
				times.pop_back();
				ClockTime* endTime = _parser.createTime(times.back());
				bool startStatus = startTime->checkOverdueTime();
				bool endStatus = endTime->checkOverdueTime();
				Date toBeSet;
				// when end time and start time set by users are both earlier than current time, set end date 
				// to tomorrow
				if(startStatus && endStatus) {
					toBeSet.setDateAsTomorrow();
					commandAdd->setEndDate(toBeSet);
				} else {
					// two possibilities current time is in between start and end time
					// or current time is earlier then start time
					//endDate is set to today
					int month = toBeSet.getCurrentMonth();
					int year = toBeSet.getCurrentYear();
					int day = toBeSet. getCurrentDay();
					Date today(day,month,year);
					commandAdd->setEndDate(today);
				}
				
				commandAdd->setStartTime(*startTime);
				commandAdd->setEndTime(*endTime);
				break;
		    }
			default:
				delete commandAdd;
				commandAdd=NULL;
				throw InvalidAddCommandInputException();
			}

		} else {
			switch(times.size()) {
			case 1:
				commandAdd->setEndTime(*_parser.createTime(times.back()));
				break;
			case 2:
				commandAdd->setEndTime(*_parser.createTime(times.back()));
				times.pop_back();
				commandAdd->setEndTime(*_parser.createTime(times.back()));
				break;
			default:
				delete commandAdd;
				commandAdd=NULL;
				throw InvalidAddCommandInputException();

			}
			

		}
		
   }

	
	commandAdd->setPreviousScreen(screen);
	commandAdd->setUserInput(parameter);
	return commandAdd;
}

	

	
Command* CommandCreator::createCommandDelete(std::string parameter,DISPLAY_TYPE* type) {
	if(_parser.isAllNumbers(parameter)) {
		unsigned int id = _parser.toNum(parameter);
		flagIndex(id);
		id = id - 1;
		Command_Delete* commandDelete = new Command_Delete;
		commandDelete->setDeletionIndex(id);
		commandDelete->setDisplayScreen(*type);
		return commandDelete;
	} else {
		throw NotANumberException();
		return NULL;
	}

}

Command* CommandCreator::createCommandEdit(vector<std::string> parameters ,DISPLAY_TYPE* displayType, std::string* userInput)
{
	Command_Edit* commandEdit = new Command_Edit;

	commandEdit->setEditIndex(_parser.toNum(parameters[0])-1);
	commandEdit->setUserInput(userInput);
	commandEdit->setDisplayScreen(*displayType);
	return commandEdit;
}


Command* CommandCreator::createCommandDone(std::string parameter,DISPLAY_TYPE* type){
	if(*type==COMPLETE){
		throw InvalidCommandWordException();
		//throw UnableToSetAsDone
	}
	if(_parser.isAllNumbers(parameter)) {
		unsigned int id = _parser.toNum(parameter);
		flagIndex(id);
		id--;
		Command_Done* commandDone = new Command_Done;
		commandDone->setCompletedIndex(id);
		commandDone->setDisplayScreen(*type);
		return commandDone;
	} else {
		throw NotANumberException();
		return NULL;
	} 
}

Command* CommandCreator::createCommandUndone(std::string parameter,DISPLAY_TYPE* type){
	if(_parser.isAllNumbers(parameter)) {
		unsigned int id = _parser.toNum(parameter);
		flagIndex(id);
		id--;
		//implement protection
		Command_Undone* commandUndone = new Command_Undone;
		commandUndone->setUncompletedIndex(id);
		commandUndone->setDisplayScreen(*type);
		return commandUndone;
	} else {
		throw NotANumberException();
		return NULL;
	}
}

Command* CommandCreator::createCommandUndo(){
	Command_Undo* newCommand = new Command_Undo;
	return newCommand;
}

Command* CommandCreator::createCommandRedo(){
	Command_Redo* newCommand = new Command_Redo;
	return newCommand;
}

Command* CommandCreator::createCommandClear(std::string parameter,DISPLAY_TYPE* type){
	Command_Clear* newCommand;
	if(parameter=="all"){
		newCommand=new Command_Clear(ALL);
	}else if(parameter=="done"){
		newCommand=new Command_Clear(COMPLETED_TASKS);
	}else if(parameter=="undone"){
		newCommand=new Command_Clear(UNCOMPLETED_TASKS);
	}else if(parameter==""){
		newCommand=new Command_Clear(SCREEN);
		newCommand->setDisplayScreen(*type);
	}else{
		throw InvalidClearCommandInputException();
	}
	return newCommand;
}

Command* CommandCreator::createCommandSearch(std::string parameter,DISPLAY_TYPE* type){
	flagArg(parameter);
	Command_Search* commandSearch = new Command_Search;
	_parser.removeWhiteSpaces(parameter);
	commandSearch->setKeyword(parameter);
	commandSearch->setPreviousScreen(type);
	return commandSearch;
}

Command* CommandCreator::createCommandFilter(std::string parameter,DISPLAY_TYPE*){
	flagArg(parameter);
	Command_Filter* commandFilter= new Command_Filter;
	commandFilter->setKeyword(parameter);
	return commandFilter;
}


std::string CommandCreator::getFeedback() {
	return _feedbackExceptiontoUI;
}

Command* CommandCreator::createCommandDisplay(string parameter, DISPLAY_TYPE* displayType)
{
	Command_Display* newCommand= new Command_Display();
	newCommand->setPreviousScreen(displayType);
	if(parameter=="main"){
		newCommand->setNextScreen(MAIN);
	}else if(parameter=="completed"||parameter=="done"){
		newCommand->setNextScreen(COMPLETE);
	}else{
		delete newCommand;
		newCommand==NULL;
		throw InvalidAddCommandInputException();
	}
	return newCommand;
}

