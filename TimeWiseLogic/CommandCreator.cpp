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



//the below methods are responsible for creating the derived commands
Command* CommandCreator::interpretCommand(std::string userInput,DISPLAY_TYPE& displayType,std::string& commandLineInput, TaskList& tasklist)
{
	try {
        string commandTypeString = Parser::getFirstWord(userInput);
		CMD_TYPE commandType = Parser::determineCommandType(commandTypeString); 

		// Assume all other commands are adding event
		if(commandType == UNDEFINED) {
			userInput = "add " + userInput;
			commandType = ADD;
		}
	
		string parameter = Parser::removeFirstWord(userInput);
		parameter = Parser::trim(parameter);
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
					return createCommandDone(parameter,&displayType);
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
					return createCommandUndone(parameter,&displayType);
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
		}
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
	} catch (InvalidFilterParameters& ifp) {
		_feedbackExceptiontoUI = ifp.what();
		throw InvalidFilterParameters();
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
			category = Parser::strReplace("#", "", descriptionWord[pos]);
			description = Parser::strReplace(descriptionWord[pos], "", description);
		}
	}
	
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
				throw InvalidAddCommandInputException();
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
				throw InvalidAddCommandInputException();
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
			if(isValidIndex(id)&&isValidDeleteIndex(id,type,tasklist)){
				id = id - 1;
				commandDelete->addDeletionIndex(id);
				commandDelete->setDisplayScreen(*type);
			} else {
				delete commandDelete;
				commandDelete=NULL;
				throw OutOfRangeException();
				return NULL;
			}
		} else {
			delete commandDelete;
			commandDelete=NULL;
			throw NotANumberException();
			return NULL;
		}
		parameter.pop_back();
	}
	return commandDelete;
}

Command* CommandCreator::createCommandDone(std::string parameter,DISPLAY_TYPE* type){
	if(*type==COMPLETE){
		
		throw UnableTosetAsDone();
		return NULL;

	}
	if(Parser::isAllNumbers(parameter)) {
		int id = Parser::toNum(parameter);
		if(isValidIndex(id)) {
		id--;
		Command_Done* commandDone = new Command_Done;
		commandDone->setCompletedIndex(id);
		commandDone->setDisplayScreen(*type);
		return commandDone;
	} else {
		throw OutOfRangeException();
		return NULL;
	}
	}
	else {
		throw NotANumberException();
		return NULL;
	} 
}

Command* CommandCreator::createCommandUndone(std::string parameter,DISPLAY_TYPE* type){
	if(Parser::isAllNumbers(parameter)) {
		int id = Parser::toNum(parameter);
		if (isValidIndex(id)) {
		id--;
		//implement protection
		Command_Undone* commandUndone = new Command_Undone;
		commandUndone->setUncompletedIndex(id);
		commandUndone->setDisplayScreen(*type);
		return commandUndone;
		} else {
			throw OutOfRangeException();
			return NULL;
		}
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

Command* CommandCreator::createCommandClear(std::string parameter,DISPLAY_TYPE* type) {
	if(parameter=="all") {
		Command_Clear* newCommand=new Command_Clear(ALL);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else if(parameter=="done") {
		Command_Clear* newCommand=new Command_Clear(COMPLETED_TASKS);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else if(parameter=="undone") {
		Command_Clear* newCommand=new Command_Clear(UNCOMPLETED_TASKS);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else if(parameter=="") {
		Command_Clear* newCommand=new Command_Clear(SCREEN);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	} else {
		throw InvalidClearCommandInputException();
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
	if(parameter[0]=='#'){
		commandFilter->setCategory(parameter.substr(1));
		return commandFilter;
	}
	Date date;
	if(Parser::isDate(parameter, date)) {
		Date* tempDate = new Date(date);
		commandFilter->setDate( tempDate );
		return commandFilter;
	} else {
		throw InvalidFilterParameters();
		//Invalid Filter parameter();
	}
	return NULL;
}

std::string CommandCreator::getFeedback() {
	return _feedbackExceptiontoUI;
}

Command* CommandCreator::createCommandDisplay(string parameter, DISPLAY_TYPE* displayType)
{
	Command_Display* newCommand= new Command_Display();
	newCommand->setCurrentScreen(displayType);
	if(parameter=="main"){
		newCommand->setNextScreen(MAIN);
	}else if(parameter=="completed"||parameter=="done"){
		newCommand->setNextScreen(COMPLETE);
	}else{
		delete newCommand;
		newCommand=NULL;
		throw InvalidAddCommandInputException();
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
			throw InvalidAddCommandInputException();
		}
	} else {
		throw InvalidAddCommandInputException();
	}
	if(index==DEFAULT_INDEX) {
		throw InvalidAddCommandInputException();
		//no index
	}

	Parser::extractDateTime(parameter, description, dates, times);
	
	vector<string> descriptionWord = Parser::explode(' ', description);
	for(int pos = descriptionWord.size()-1 ; category.empty() && pos>=0 ; pos--) {
		if(Parser::isCategory(descriptionWord[pos])) {
			category = Parser::strReplace("#", "", descriptionWord[pos]);
			description = Parser::strReplace(descriptionWord[pos], "", description);
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
			commandEdit=NULL;
			throw InvalidAddCommandInputException();
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
			throw InvalidAddCommandInputException();
		}
	}

	commandEdit->setIndex(index);
	commandEdit->setDisplayScreen(*screen);
	return commandEdit;
}

bool CommandCreator::isValidDeleteIndex(int id,DISPLAY_TYPE* type,TaskList& tasklist){
	switch(*type){
	case MAIN:
		if(id>tasklist.undoneSize()){
			return false;
		}
		break;
	case COMPLETE:
		if(id>tasklist.doneSize()){
			return false;
		}
		break;
	case SEARCH:{
		int size = tasklist.getSearchResults().size();
		if(id>size){
			return false;
		}
		break;
				}
	case FILTERED:{
		int size = tasklist.getFilterResults().size();
		if(id>size){
			return false;
		}
		break;
				  }
	}
	return true;
}
