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

		string commandTypeString = _parser.getFirstWord(userInput);
		CMD_TYPE commandType = _parser.determineCommandType(commandTypeString); 

		// Assume all other commands are adding event
		if(commandType == UNDEFINED) {
			userInput = "add " + userInput;
			commandType = ADD;
		}
	
		string parameter = _parser.removeFirstWord(userInput);
		_parser.removeWhiteSpaces(parameter);
		vector<string> parameters = _parser.splitBySpace(parameter);
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
			case BLOCK:
				return createCommandBlock(parameter,&displayType);
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
		if(_parser.isCategory(param[pos]) && category.empty()) {
			category = _parser.replaceWord("#", "", param[pos]);
			descriptionWord[pos] = false;	// It is a category, so it is not a part of description.
		} else if(_parser.extractDate(command, pos)[3]) {
				vector<int> dateData = _parser.extractDate(command, pos);
				dates.push_back(Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]));

				for(int i=0 ; i<dateData[3] ; i++) {
					descriptionWord[pos - i] = false;
				}
				pos = pos - (dateData[3] - 1);

				// Check preposition
				if( (pos-1) >= 0 && _parser.isPreposition(param[pos-1]) ) {
					descriptionWord[pos - 1] = false;
				}
			
		} else if(_parser.extractTime(command, pos)[1]) {
			vector<int> timeData = _parser.extractTime(command, pos);
			times.push_back(Parser::strVal(timeData[0]));
			descriptionWord[pos] = false;

			// Check preposition
			if( (pos-1) >= 0 && _parser.isPreposition(param[pos-1]) ) {
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

	_parser.removeWhiteSpaces(description);
	if (hasArg(description)) {
	Command_Add* commandAdd = new Command_Add;

	if(category!="") {
		commandAdd->setCategory(category);
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
				commandAdd->setStartTime(*_parser.createTime(times.back()));
				times.pop_back();
				commandAdd->setEndTime(*_parser.createTime(times.back()));
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
	if(_parser.isAllNumbers(parameter)) {
		int id = _parser.toNum(parameter);
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
	if(_parser.isAllNumbers(parameter)) {
		int id = _parser.toNum(parameter);
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
	if(_parser.isAllNumbers(parameter)) {
		int id = _parser.toNum(parameter);
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
	_parser.removeWhiteSpaces(parameter);
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
	if(_parser.isDateFormat(parameter)){
		vector<int> dateData = _parser.extractDate(parameter, -1);
		std::string dateString = Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]);
		Date* date=_parser.createDate(dateString);
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
		if(_parser.isCategory(param[pos]) && category.empty()) {
			category = _parser.replaceWord("#", "", param[pos]);
			descriptionWord[pos] = false;	// It is a category, so it is not a part of description.
		} else if(_parser.extractDate(command, pos)[3]) {
			vector<int> dateData = _parser.extractDate(command, pos);
			dates.push_back(Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]));

			for(int i=0 ; i<dateData[3] ; i++) {
				descriptionWord[pos - i] = false;
			}
			pos = pos - (dateData[3] - 1);

			// Check preposition
			if( (pos-1) >= 0 && _parser.isPreposition(param[pos-1]) ) {
				descriptionWord[pos - 1] = false;
			}
		} else if(_parser.extractTime(command, pos)[1]) {
			vector<int> timeData = _parser.extractTime(command, pos);
			times.push_back(Parser::strVal(timeData[0]));
			descriptionWord[pos] = false;

			// Check preposition
			if( (pos-1) >= 0 && _parser.isPreposition(param[pos-1]) ) {
				descriptionWord[pos - 1] = false;
			}
		} else if(_parser.isAllNumbers(param[pos])) {
			index = _parser.toNum(param[pos]);
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

	_parser.removeWhiteSpaces(description);

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
			commandEdit->setEndDate(_parser.createDate(dates.back()));
			break;
		case 2:
			commandEdit->setStartDate(_parser.createDate(dates.back()));
			dates.pop_back();
			commandEdit->setEndDate(_parser.createDate(dates.back()));
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
				commandEdit->setEndTime(_parser.createTime(times.back()));
				break;
			case 2:
				commandEdit->setStartTime(_parser.createTime(times.back()));
				times.pop_back();
				commandEdit->setEndTime(_parser.createTime(times.back()));
				break;
			default:
				delete commandEdit;
				commandEdit=NULL;
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

Command* CommandCreator::createCommandBlock(std::string parameter,DISPLAY_TYPE* screen){
	std::vector<std::string> components;
	std::vector<std::string> times;
	std::vector<std::string> dates;
	std::string part;
	std::string category;
	Date* startDate=NULL;
	Date* endDate=NULL;
	ClockTime* startTime=NULL;
	ClockTime* endTime=NULL;
	Command_Block* newCommand= new Command_Block;
	components=_parser.explode('\\',parameter);
	//std::vector<std::string> tokens;
	//tokens=_parser.splitBySpace(components.top);
	std::string description = components.front();
	newCommand->setDescription(description);
	components.erase(components.begin());

	for(unsigned int i=0 ; i<components.size() ; i++) {
		vector<string> token = _parser.explode(' ', components[i]);
		int temp; // storing the word number used for the date/time
		for(int j = token.size()-1 ; j>=0 ; j--) {
			if(temp = _parser.extractDate(components[i], j)[3]) {
				vector<int> dateData = _parser.extractDate(components[i], j);
				dates.push_back(Parser::strVal(dateData[2]) + "/" + Parser::strVal(dateData[1]) + "/" + Parser::strVal(dateData[0]));
				j = j - (temp-1);
			} else if(temp = _parser.extractTime(components[i], j)[1]) {
				vector<int> timeData = _parser.extractTime(components[i], j);
				times.push_back(Parser::strVal(timeData[0]));			
				j = j - (temp-1);
			} else if(_parser.isCategory(token[j])){
				std::string cat=_parser.replaceWord("#","",token[j]);
				newCommand->setCategory(cat);
			}
			
		}
		if(dates.size()==1){
			endDate=_parser.createDate(dates[0]);
		}else if(dates.size()==2){
			endDate=_parser.createDate(dates[0]);
			startDate=_parser.createDate(dates[1]);
		}else{
			//throw exception
		}
		if(times.size()==1){
			endTime=_parser.createTime(times[0]);
		}else if(times.size()==2){
			endTime=_parser.createTime(times[0]);
			startTime=_parser.createTime(times[1]);
		}
		newCommand->addSchedule(startDate,endDate,startTime,endTime);
		startDate=NULL;
		endDate=NULL;
		startTime=NULL;
		endTime=NULL;
		dates.clear();
		times.clear();
	}
	newCommand->setPreviousScreen(screen);
	return newCommand;
}
