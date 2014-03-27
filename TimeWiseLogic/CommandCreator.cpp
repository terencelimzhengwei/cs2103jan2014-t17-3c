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

/*void CommandCreator::flagDescription(std::string input){
	if (input.length() == 0 ) {
		throw InvalidAddCommandInputException();
	}
}*/

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
		if(tasklist.checkEditStatus()){
			userInput="add " + userInput;
			commandType = ADDEDIT;
		}else if(commandType==UNDEFINED) {
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
			case ADDEDIT:
				return createCommandAddEdit(parameter,parameterNum,parameters,&displayType);
			case DELETE: {
				if(hasArg(parameter)) {
					return createCommandDelete(parameter,&displayType);
				} else {
					throw NoArgumentException();
					return NULL;
				}
				
			}
			case EDIT: {
				if (hasArg(parameter)) {
					return createCommandEdit(parameters,&displayType,&commandLineInput);
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
	}

}

Command* CommandCreator::createCommandAdd(string command, int parameterNum, vector<string> param, DISPLAY_TYPE* screen) {
	bool* descriptionWord = new bool[param.size()];
	string category;
	string priority;
	string description;
	vector<string> dates;
	vector<string> times;

	memset(descriptionWord, true, sizeof descriptionWord);	// Assume all words in the command are descriptions first.

	for(int pos = param.size()-1 ; pos>0 ; pos--) {
		if(_parser.isCategory(param[pos]) && category.empty()) {
			category = _parser.replaceWord("#", "", param[pos]);
			descriptionWord[pos] = false;	// It is a category, so it is not a part of description.
		} else if(_parser.isPriority(param[pos]) && priority.empty()) {
			priority = _parser.replaceWord("!", "", param[pos]);
			descriptionWord[pos] = false;	// It is a priority, so it is not a part of description.
		} else if(_parser.extractDate(command, pos)[3]) {
			vector<int> dateData = _parser.extractDate(command, pos);
			dates.push_back(_parser.strval(dateData[2]) + "/" + _parser.strval(dateData[1]) + "/" + _parser.strval(dateData[0]));

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
			times.push_back(_parser.strval(timeData[0]));
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
				commandAdd->setStartTime(*_parser.createTime(times.back()));
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
	return commandAdd;
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

Command* CommandCreator::createCommandEdit(vector<std::string> parameters ,DISPLAY_TYPE* displayType, std::string* userInput)
{
	
	int id = _parser.toNum(parameters[0]);
	if (isValidIndex(id)) {
		Command_Edit* commandEdit = new Command_Edit;
		commandEdit->setEditIndex(id -1 );
		commandEdit->setUserInput(userInput);
		commandEdit->setDisplayScreen(*displayType);
		return commandEdit;
	} else {
		throw OutOfRangeException();
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
	Command_Search* commandSearch = new Command_Search;
	_parser.removeWhiteSpaces(parameter);
	commandSearch->setKeyword(parameter);
	commandSearch->setPreviousScreen(type);
	return commandSearch;
}

Command* CommandCreator::createCommandFilter(std::string parameter,DISPLAY_TYPE*){
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

Command* CommandCreator::createCommandAddEdit(string command, int parameterNum, vector<string> param, DISPLAY_TYPE* screen){
	bool* descriptionWord = new bool[param.size()];
	string category;
	string priority;
	string description;
	vector<string> dates;
	vector<string> times;

	memset(descriptionWord, true, sizeof descriptionWord);	// Assume all words in the command are descriptions first.

	for(int pos = param.size()-1 ; pos>0 ; pos--) {
		if(_parser.isCategory(param[pos]) && category.empty()) {
			category = _parser.replaceWord("#", "", param[pos]);
			descriptionWord[pos] = false;	// It is a category, so it is not a part of description.
		} else if(_parser.isPriority(param[pos]) && priority.empty()) {
			priority = _parser.replaceWord("!", "", param[pos]);
			descriptionWord[pos] = false;	// It is a priority, so it is not a part of description.
		} else if(_parser.extractDate(command, pos)[3]) {
			vector<int> dateData = _parser.extractDate(command, pos);
			dates.push_back(_parser.strval(dateData[2]) + "/" + _parser.strval(dateData[1]) + "/" + _parser.strval(dateData[0]));

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
			times.push_back(_parser.strval(timeData[0]));
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

	Command_AddEdit* commandAdd = new Command_AddEdit;

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
				commandAdd->setStartTime(*_parser.createTime(times.back()));
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
	return commandAdd;
}