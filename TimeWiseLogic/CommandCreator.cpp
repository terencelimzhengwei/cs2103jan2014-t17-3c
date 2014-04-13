#include "CommandCreator.h"


CommandCreator::CommandCreator(void){
}


CommandCreator::~CommandCreator(void){
}


bool CommandCreator::hasArg(std::string input){
	if (input.length() == 0) {
		return false;
	}
	return true;
}


bool CommandCreator::isValidIndex(int id) {
	if (id < 0 || id == 0) {
		return false;
	}
	return true;
}

bool CommandCreator::isValidRemovalIndex(int id, DISPLAY_TYPE* type, TaskList& tasklist){
	switch(*type){
	case MAIN:
		if(id > tasklist.undoneSize()){
			return false;
		} 
		break;
	case COMPLETE:
		if(id > tasklist.doneSize()){
			return false;
		}
		break;
	case SEARCH:{
		int size = tasklist.getSearchResults().size();
		if(id > size){
			return false;
		}
		break;
				}
	case FILTERED:{
		int size = tasklist.getFilterResults().size();
		if(id > size){
			return false;
		}
		break;
				  }
	}
	return true;
}
void CommandCreator::manipulateInputWithoutCommandWord(CMD_TYPE& commandType, std::string& userInput) {
	userInput = CMD_TYPE_STRING[0] + SPACE_PARAMETER + userInput;
	commandType = ADD;
}
CMD_TYPE CommandCreator::extractCommandType(std::string userInput) {
	string commandTypeString = Parser::getFirstWord(userInput);
	CMD_TYPE type = Parser::determineCommandType(commandTypeString); 
	return type;
}

std::string CommandCreator::extractUserInput(std::string userInput) {
	string parameter = Parser::removeFirstWord(userInput);
	parameter = Parser::trim(parameter);
	return parameter;
}
//the below methods are responsible for creating the derived commands
Command* CommandCreator::interpretCommand(std::string userInput,DISPLAY_TYPE& displayType,std::string& commandLineInput, TaskList& tasklist)
{
	try {
		CMD_TYPE commandType = extractCommandType(userInput);
		// Assume all other commands are adding event
		if(commandType == UNDEFINED) {
			manipulateInputWithoutCommandWord(commandType,userInput);
		}
		string parameter = extractUserInput(userInput);
		vector<string> parameters = Parser::splitBySpace(parameter);
		int parameterNum = parameters.size();
		switch (commandType) {
		case ADD: {
			if(hasArg(parameter)) {
				return createCommandAdd(parameter,parameterNum,parameters,&displayType);
			} else {
				throw NoArgumentException();
				return NULL;
			}
				  }
		case DELETE: {
			if(hasArg(parameter)) {
				return createCommandDelete(parameters,&displayType,tasklist);
			} else {
				throw NoArgumentException();
				return NULL;
			}

					 }
		case EDIT:{
			if(hasArg(parameter)) {
				return createCommandEdit(parameter,parameterNum,parameters,&displayType);
			} else {
				throw NoArgumentException();
				return NULL;
			}
				  }
		case DONE: {
			if(hasArg(parameter)) {
				return createCommandDone(parameters,&displayType,tasklist);
			} else {
				throw NoArgumentException();
				return NULL;
			}

				   }
		case FILTER: {
			if(hasArg(parameter)){
				return createCommandFilter(parameter,&displayType);
			}else{
				throw NoArgumentException();
				return NULL;
			}
					 }
		case UNDONE: {
			if(hasArg(parameter)) {
				return createCommandUndone(parameters,&displayType,tasklist);
			} else {
				throw NoArgumentException();
				return NULL;
			}
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
			if (hasArg(parameter)) {
				return createCommandSearch(parameter,&displayType);
			} else {
				throw NoArgumentException();
				return NULL;
			}

					 }
		case DISPLAY:
			return createCommandDisplay(parameter,&displayType);
		default: {
			return NULL;
				 }
		}// All exceptions are caught here
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
	} catch (InvalidDateTimeFormatException& idtfe) {
		_feedbackExceptiontoUI = idtfe.what();
		throw InvalidDateTimeFormatException();
	} catch (InvalidFilterCommandInputException& ifp) {
		_feedbackExceptiontoUI = ifp.what();
		throw InvalidFilterCommandInputException();
	} catch (UnableToSetAsDone& utsad){
		_feedbackExceptiontoUI = utsad.what();
		throw UnableToSetAsDone();
	} catch (UnableToUndoneUncompletedTasks& utuuct){
		_feedbackExceptiontoUI = utuuct.what();
		throw UnableToUndoneUncompletedTasks();
	} catch (InvalidClearCommandInputException& icie){
		_feedbackExceptiontoUI = icie.what();
		throw InvalidClearCommandInputException();
	} catch (InvalidDisplayCommandException& idc) {
		_feedbackExceptiontoUI = idc.what();
		throw InvalidDisplayCommandException();
	}

}

Command* CommandCreator::createCommandAdd(string command, int parameterNum, vector<string> param, DISPLAY_TYPE* screen) {
	string category;
	string description;

	vector<Date> dates;
	vector<ClockTime> times;
	Parser::extractDateTime(command, description, dates, times);

	vector<string> descriptionWord = Parser::explode(' ', description);
	for(int pos = descriptionWord.size()-1 ; category.empty() && pos>=0 ; pos--) {
		if(Parser::isCategory(descriptionWord[pos])) {
			category = Parser::strReplace(CATEGORY_SPECIFIER, DEFAULT_EMPTY, descriptionWord[pos]);
			description = Parser::strReplace(descriptionWord[pos], DEFAULT_EMPTY, description);
		}
	}
	//If there is a task description
	if(hasArg(description)) {
		Command_Add* commandAdd = new Command_Add;

		if(!category.empty()) {
			commandAdd->setCategory(category);
		}

		commandAdd->setDescription(description);

		if(!dates.empty()) {
			switch(dates.size()) {
			case 1:
				commandAdd->setEndDate(dates[0]);
				break;
			case 2:
				commandAdd->setStartDate(dates[1]);
				commandAdd->setEndDate(dates[0]);
				break;
			default:
				delete commandAdd;
				commandAdd = NULL;
				throw InvalidDateTimeFormatException();
			}
		}

		if(!times.empty()) {
			switch(times.size()) {
			case 1:
				commandAdd->setEndTime(times[0]);
				break;
			case 2:
				commandAdd->setStartTime(times[1]);
				commandAdd->setEndTime(times[0]);
				break;
			default:
				delete commandAdd;
				commandAdd = NULL;
				throw InvalidDateTimeFormatException();
			}
		}
		commandAdd->setPreviousScreen(screen);
		return commandAdd;
	} else {
		throw InvalidAddCommandInputException();
		return NULL;
	}
}

Command* CommandCreator::createCommandDelete(vector<string> parameter,DISPLAY_TYPE* type,TaskList& tasklist) {
	Command_Delete* commandDelete = new Command_Delete;
	while(!parameter.empty()){
		if(Parser::isAllNumbers(parameter.back())) {
			int id = Parser::toNum(parameter.back());
			if(isValidIndex(id) && isValidRemovalIndex(id,type,tasklist)){
				id = id - 1;
				commandDelete->addDeletionIndex(id);
				commandDelete->setDisplayScreen(*type);
			} else {
				delete commandDelete;
				commandDelete = NULL;
				throw OutOfRangeException();
				return NULL;
			}
		} else {
			delete commandDelete;
			commandDelete = NULL;
			throw NotANumberException();
			return NULL;
		}
		parameter.pop_back();
	}
	return commandDelete;
}

Command* CommandCreator::createCommandDone(vector<string> parameter,DISPLAY_TYPE* type,TaskList& tasklist){
	if(*type == COMPLETE){
		throw UnableToSetAsDone();
		return NULL;

	}
	Command_Done* commandDone = new Command_Done;
	while(!parameter.empty()){
		if(Parser::isAllNumbers(parameter.back())){
			int id = Parser::toNum(parameter.back());
			if(isValidIndex(id) && isValidRemovalIndex(id,type,tasklist)) {
				id--;
				commandDone->addDoneIndex(id);
				parameter.pop_back();
			} else {
				delete commandDone;
				commandDone = NULL;
				throw OutOfRangeException();
				return NULL;
			}
		}
		else {
			delete commandDone;
			commandDone = NULL;
			throw NotANumberException();
			return NULL;
		} 
	}
	commandDone->setPreviousScreen(type);
	return commandDone;
}

Command* CommandCreator::createCommandUndone(vector<string> parameter,DISPLAY_TYPE* type,TaskList& tasklist)
{
	Command_Undone* commandUndone = new Command_Undone;
	while(!parameter.empty()){
		if(Parser::isAllNumbers(parameter.back())){
			int id = Parser::toNum(parameter.back());
			if(isValidIndex(id)&&isValidRemovalIndex(id,type,tasklist)) {
				id--;
				commandUndone->addUndoneIndex(id);
				parameter.pop_back();
			} else {
				delete commandUndone;
				commandUndone = NULL;
				throw OutOfRangeException();
				return NULL;
			}
		}
		else {
			delete commandUndone;
			commandUndone = NULL;
			throw NotANumberException();
			return NULL;
		} 
	}
	commandUndone->setPreviousScreen(type);
	return commandUndone;
}

Command* CommandCreator::createCommandUndo(){
	Command_Undo* newCommand = new Command_Undo;
	return newCommand;
}

Command* CommandCreator::createCommandRedo(){
	Command_Redo* newCommand = new Command_Redo;
	return newCommand;
}

Command* CommandCreator::createCommandClear(std::string parameter,DISPLAY_TYPE* type) {
	if(parameter == CLEAR_TYPE_STRING[ALL] ) {
		Command_Clear* newCommand=new Command_Clear(ALL);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else if(parameter == CLEAR_TYPE_STRING[COMPLETED_TASKS]) {
		Command_Clear* newCommand = new Command_Clear(COMPLETED_TASKS);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else if(parameter == CLEAR_TYPE_STRING[UNCOMPLETED_TASKS]) {
		Command_Clear* newCommand = new Command_Clear(UNCOMPLETED_TASKS);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else if(parameter == CLEAR_TYPE_STRING[SCREEN]) {
		Command_Clear* newCommand = new Command_Clear(SCREEN);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else {
		throw InvalidClearCommandInputException();
		return NULL;
	}
	return NULL;
}

Command* CommandCreator::createCommandSearch(std::string parameter,DISPLAY_TYPE* type) {
	Command_Search* commandSearch = new Command_Search;
	parameter = Parser::trim(parameter);
	commandSearch->setKeyword(parameter);
	commandSearch->setPreviousScreen(type);
	return commandSearch;
}

Command* CommandCreator::createCommandFilter(std::string parameter,DISPLAY_TYPE* screen) {
	Command_Filter* commandFilter= new Command_Filter();
	commandFilter->setPreviousScreen(screen);
	if(parameter[0] == TASK_SPECIFIER){
		commandFilter->setCategory(parameter.substr(1));
		return commandFilter;
	}
	Date date;
	if(Parser::isDate(parameter, date)) {
		Date* tempDate = new Date(date);
		commandFilter->setDate( tempDate );
		return commandFilter;
	} else {
		throw InvalidFilterCommandInputException();
	}
	return NULL;
}

std::string CommandCreator::getFeedback() {
	return _feedbackExceptiontoUI;
}

Command* CommandCreator::createCommandDisplay(string parameter, DISPLAY_TYPE* displayType)
{
	Command_Display* newCommand = new Command_Display();
	newCommand->setCurrentScreen(displayType);
	if(parameter == DISPLAY_TYPE_STRING[MAIN]){
		newCommand->setNextScreen(MAIN);
	}else if(parameter == DISPLAY_TYPE_STRING[COMPLETED] || parameter == DISPLAY_TYPE_STRING[DONE_DISPLAY]){
		newCommand->setNextScreen(COMPLETE);
	}else{
		delete newCommand;
		newCommand = NULL;
		throw InvalidDisplayCommandException();
	}
	return newCommand;
}

Command* CommandCreator::createCommandEdit(string parameter, int parameterNum, vector<string> param, DISPLAY_TYPE* screen) {
	string category;
	string parameters;
	string description;
	int index = DEFAULT_INDEX;
	vector<Date> dates;
	vector<ClockTime> times;
	smatch sm;

	if( regex_match(parameter, sm, regex("^\\s*([0-9]*) (.+)\\s*$")) ) {
		if( isValidIndex(Parser::toNum(sm[1])) ) {
			index = Parser::toNum(sm[1]) - 1;
			parameter = sm[2];
		} else {
			throw NotANumberException();
		}
	} else {
		throw InvalidEditCommandInputException();
	}
	if(index == DEFAULT_INDEX) {
		throw InvalidEditCommandInputException();
		
	}

	Parser::extractDateTime(parameter, description, dates, times);

	vector<string> descriptionWord = Parser::explode(SPACE_DELIMITER, description);
	for(int pos = descriptionWord.size() - 1 ; category.empty() && pos >= 0 ; pos--) {
		if(Parser::isCategory(descriptionWord[pos])) {
			category = Parser::strReplace(CATEGORY_SPECIFIER, DEFAULT_EMPTY, descriptionWord[pos]);
			description = Parser::strReplace(descriptionWord[pos], DEFAULT_EMPTY, description);
		}
	}

	description = Parser::trim(description);

	Command_Edit* commandEdit = new Command_Edit();
	if( !description.empty() ){
		commandEdit->setDescription(description);
	}
	if( !category.empty() ) {
		commandEdit->setCategory(category);
	}
	if( !dates.empty() ) {
		Date* tempDate;
		switch(dates.size()) {
		case 1:
			tempDate = new Date( dates[0] );
			commandEdit->setEndDate( tempDate );
			break;
		case 2:
			tempDate = new Date( dates[1] );
			commandEdit->setStartDate( tempDate );
			tempDate = new Date( dates[0] );
			commandEdit->setEndDate( tempDate );
			break;
		default:
			delete commandEdit;
			commandEdit = NULL;
			throw InvalidDateTimeFormatException();
		}
	}
	if(!times.empty()) {
		ClockTime* tempTime;
		switch(times.size()) {
		case 1: {
			tempTime = new ClockTime( times[0] );
			commandEdit->setEndTime( tempTime );
			break;
				}
		case 2:
			tempTime = new ClockTime( times[1] );
			commandEdit->setStartTime( tempTime );
			times.pop_back();
			tempTime = new ClockTime( times[0] );
			commandEdit->setEndTime( tempTime );
			break;
		default:
			delete commandEdit;
			commandEdit = NULL;
			throw InvalidDateTimeFormatException();
		}
	}

	commandEdit->setIndex(index);
	commandEdit->setDisplayScreen(*screen);
	return commandEdit;
}


