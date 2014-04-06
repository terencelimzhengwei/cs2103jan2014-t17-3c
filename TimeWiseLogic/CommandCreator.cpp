#include "CommandCreator.h"


CommandCreator::CommandCreator(void)
{
}


CommandCreator::~CommandCreator(void)
{
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
					return createCommandDelete(parameter,&displayType);
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
	} catch (InvalidHeaderException& ihe) {
		_feedbackExceptiontoUI = ihe.what();
		throw InvalidHeaderException();
	} catch (InvalidDateTimeFormatException& idtfe) {
		_feedbackExceptiontoUI = idtfe.what();
		throw InvalidDateTimeFormatException();
	}

}

Command* CommandCreator::createCommandAdd(string command, int parameterNum, vector<string> param, DISPLAY_TYPE* screen) {
	bool* descriptionWord = new bool[param.size()];//rmb to delete this in destructor
	string category;
	string description;
	vector<string> dates;
	vector<string> times;

	memset(descriptionWord, true, sizeof descriptionWord);	// Assume all words in the command are descriptions first.

	for(int pos = param.size()-1 ; pos>0 ; pos--) {
		if(Parser::isCategory(param[pos]) && category.empty()) {
			category = Parser::strReplace("#", "", param[pos]);
			descriptionWord[pos] = false;	// It is a category, so it is not a part of description.
		} else if(Parser::extractDate(command, pos)[3]) {
				vector<int> dateData = Parser::extractDate(command, pos);
				dates.push_back(Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]));

				for(int i=0 ; i<dateData[3] ; i++) {
					descriptionWord[pos - i] = false;
				}
				pos = pos - (dateData[3] - 1);

				// Check preposition
				if( (pos-1) >= 0 && Parser::isPreposition(param[pos-1]) ) {
					descriptionWord[pos - 1] = false;
				}
			
		} else if(Parser::extractTime(command, pos)[1]) {
			vector<int> timeData = Parser::extractTime(command, pos);
			times.push_back(Parser::strVal(timeData[0]));
			descriptionWord[pos] = false;

			// Check preposition
			if( (pos-1) >= 0 && Parser::isPreposition(param[pos-1]) ) {
				descriptionWord[pos - 1] = false;
			}
		}
	}

	for(unsigned int pos=0 ; pos<param.size(); pos++) {
		if(descriptionWord[pos]) {
			if(description.empty()) {
				description = param[pos];
			} else {
				description = description + " " + param[pos];
			}
		}
	}
	//delete descriptionWord;

	description = Parser::trim(description);
	if (hasArg(description)) {
	Command_Add* commandAdd = new Command_Add;

	if(category!="") {
		commandAdd->setCategory(category);
	}

	commandAdd->setDescription(description);

	if(!dates.empty()) {
		switch(dates.size()){
		case 1:
			commandAdd->setEndDate(*Parser::createDate(dates.back()));
			break;
		case 2:
			commandAdd->setStartDate(*Parser::createDate(dates.back()));
			dates.pop_back();
			commandAdd->setEndDate(*Parser::createDate(dates.back()));
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
				ClockTime* endTime = Parser::createTime(times.back());
				bool timeStatus = endTime->checkOverdueTime();
				Date* toBeSet = new Date();
				// when current time is later than time set by user, set end date 
				// to tomorrow
				if(timeStatus) {
					toBeSet->setDateAsTomorrow();
					commandAdd->setEndDate(*toBeSet);
				} else {
					//when current time is earlier than the time set by user, 
					//set end date to today
					int month = toBeSet->getCurrentMonth();
					int year = toBeSet->getCurrentYear();
					int day = toBeSet->getCurrentDay();
					Date* today=new Date(day,month,year);
					commandAdd->setEndDate(*today);
				}
				commandAdd->setEndTime(*endTime);
				break;
		  }
			case 2:{
				// compare the time set by users with the current time
				ClockTime* startTime = Parser::createTime(times.back());
				times.pop_back();
				ClockTime* endTime = Parser::createTime(times.back());
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
				commandAdd->setEndTime(*Parser::createTime(times.back()));
				break;
			case 2:
				commandAdd->setStartTime(*Parser::createTime(times.back()));
				times.pop_back();
				commandAdd->setEndTime(*Parser::createTime(times.back()));
				break;
			default:
				delete commandAdd;
				commandAdd = NULL;
				throw InvalidAddCommandInputException();

			}
			

		}
		
   }

	commandAdd->setPreviousScreen(screen);
	return commandAdd;
} else {
	throw InvalidAddCommandInputException();
	return NULL;
}
}

	

	
Command* CommandCreator::createCommandDelete(std::string parameter,DISPLAY_TYPE* type) {
	if(Parser::isAllNumbers(parameter)) {
		int id = Parser::toNum(parameter);
		if(isValidIndex(id)){
		id = id - 1;
		Command_Delete* commandDelete = new Command_Delete;
		commandDelete->setDeletionIndex(id);
		commandDelete->setDisplayScreen(*type);
		return commandDelete;
		} else {
			throw OutOfRangeException();
			return NULL;
		}
	} else {
		throw NotANumberException();
		return NULL;
	}

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

Command* CommandCreator::createCommandClear(std::string parameter,DISPLAY_TYPE* type){
	if(parameter=="all"){
		Command_Clear* newCommand=new Command_Clear(ALL);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	}else if(parameter=="done"){
		Command_Clear* newCommand=new Command_Clear(COMPLETED_TASKS);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	}else if(parameter=="undone"){
		Command_Clear* newCommand=new Command_Clear(UNCOMPLETED_TASKS);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	}else if(parameter==""){
		Command_Clear* newCommand=new Command_Clear(SCREEN);
		newCommand->setDisplayScreen(*type);
		return newCommand;
	}else{
		throw InvalidClearCommandInputException();
	}
	return NULL;
}

Command* CommandCreator::createCommandSearch(std::string parameter,DISPLAY_TYPE* type){
	Command_Search* commandSearch = new Command_Search;
	parameter = Parser::trim(parameter);
	commandSearch->setKeyword(parameter);
	commandSearch->setPreviousScreen(type);
	return commandSearch;
}

Command* CommandCreator::createCommandFilter(std::string parameter,DISPLAY_TYPE* screen){
	Command_Filter* commandFilter= new Command_Filter();
	commandFilter->setPreviousScreen(screen);
	if(parameter[0]=='#'){
		commandFilter->setCategory(parameter.substr(1));
		return commandFilter;
	}
	if(Parser::isDateFormat(parameter)){
		vector<int> dateData = Parser::extractDate(parameter, -1);
		std::string dateString = Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]);
		Date* date = Parser::createDate(dateString);
		commandFilter->setDate(date);
		delete date;
		date=NULL;
		return commandFilter;

	}else{
		throw InvalidAddCommandInputException();
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

Command* CommandCreator::createCommandEdit(string command, int parameterNum, vector<string> param, DISPLAY_TYPE* screen){
	bool* descriptionWord = new bool[param.size()];//rmb to delete this in destructor
	string category;
	string priority;
	string description;
	int index=DEFAULT_INDEX;
	vector<string> dates;
	vector<string> times;

	memset(descriptionWord, true, sizeof descriptionWord);	// Assume all words in the command are descriptions first.

	for(int pos = param.size()-1 ; pos>=0 ; pos--) {
		if(Parser::isCategory(param[pos]) && category.empty()) {
			category = Parser::strReplace("#", "", param[pos]);
			descriptionWord[pos] = false;	// It is a category, so it is not a part of description.
		} else if(Parser::extractDate(command, pos)[3]) {
			vector<int> dateData = Parser::extractDate(command, pos);
			dates.push_back(Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]));

			for(int i=0 ; i<dateData[3] ; i++) {
				descriptionWord[pos - i] = false;
			}
			pos = pos - (dateData[3] - 1);

			// Check preposition
			if( (pos-1) >= 0 && Parser::isPreposition(param[pos-1]) ) {
				descriptionWord[pos - 1] = false;
			}
		} else if(Parser::extractTime(command, pos)[1]) {
			vector<int> timeData = Parser::extractTime(command, pos);
			times.push_back(Parser::strVal(timeData[0]));
			descriptionWord[pos] = false;

			// Check preposition
			if( (pos-1) >= 0 && Parser::isPreposition(param[pos-1]) ) {
				descriptionWord[pos - 1] = false;
			}
		} else if(Parser::isAllNumbers(param[pos])) {
			index = Parser::toNum(param[pos]);
			if (isValidIndex(index)){
				index--;
				descriptionWord[pos] = false;
			}else{
				throw InvalidAddCommandInputException();
				//invalid Index for edit;
			}
		}
	}
	if(index==DEFAULT_INDEX){
		throw InvalidAddCommandInputException();
		//no index
	}
	

	for(unsigned int pos=0 ; pos<param.size(); pos++) {
		if(descriptionWord[pos]) {
			if(description.empty()) {
				description = param[pos];
			} else {
				description = description + " " + param[pos];
			}
		}
	}
	//delete descriptionWord;

	description = Parser::trim(description);

	Command_Edit* commandEdit = new Command_Edit();
	if(description!=""){
		commandEdit->setDescription(description);
	}
	if(category!="") {
		commandEdit->setCategory(category);
	}
	if(!dates.empty()) {
		switch(dates.size()){
		case 1:
			commandEdit->setEndDate(Parser::createDate(dates.back()));
			break;
		case 2:
			commandEdit->setStartDate(Parser::createDate(dates.back()));
			dates.pop_back();
			commandEdit->setEndDate(Parser::createDate(dates.back()));
			break;
		default:
			delete commandEdit;
			commandEdit=NULL;
			throw InvalidAddCommandInputException();
		}
	}
	if(!times.empty()) {
			switch(times.size()) {
			case 1:
				commandEdit->setEndTime(Parser::createTime(times.back()));
				break;
			case 2:
				commandEdit->setStartTime(Parser::createTime(times.back()));
				times.pop_back();
				commandEdit->setEndTime(Parser::createTime(times.back()));
				break;
			default:
				delete commandEdit;
				commandEdit = NULL;
				throw InvalidAddCommandInputException();
			}
		}
	if(index==DEFAULT_INDEX){
		throw InvalidAddCommandInputException();
		//Exception
	}
	commandEdit->setIndex(index);
	commandEdit->setDisplayScreen(*screen);
	return commandEdit;
}