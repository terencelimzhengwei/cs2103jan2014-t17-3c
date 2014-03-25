#include "CommandCreator.h"


CommandCreator::CommandCreator(void)
{
}


CommandCreator::~CommandCreator(void)
{
}


void CommandCreator::flagArg(std::string input){
	if (input == "") {
		throw NoArgumentException();
	}
}

void CommandCreator::flagDescription(std::string input){
	if (input == "" ) {
		throw InvalidAddCommandInputException();
	}
}

void CommandCreator::flagIndex(unsigned int id) {
	if (id < 0) {
		throw OutOfRangeException();
	}
}



	//the below methods are responsible for creating the derived commands
Command* CommandCreator::interpretCommand(std::string userInput,DISPLAY_TYPE& displayType)
{
	try {
	string commandTypeString = _parser.getFirstWord(userInput);
	CMD_TYPE commandType = _parser.determineCommandType(commandTypeString);
	
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
				return createCommandEdit(parameters,&displayType);
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
		_feedbackExceptiontoUI.push_back(icwe.what());
		throw InvalidCommandWordException();
	} catch (NoArgumentException& nae) {
		_feedbackExceptiontoUI.push_back(nae.what());
		throw NoArgumentException();
	} catch (InvalidAddCommandInputException& iacie) {
		_feedbackExceptiontoUI.push_back(iacie.what());
		throw InvalidAddCommandInputException();
	} catch (OutOfRangeException& oore) {
		_feedbackExceptiontoUI.push_back(oore.what());
		throw OutOfRangeException();
	} catch (NotANumberException& nane) {
		_feedbackExceptiontoUI.push_back(nane.what());
		throw NotANumberException();
	}

}

Command* CommandCreator::createCommandAdd(std::string parameter, unsigned int parameterNum, vector<std::string> parameters,DISPLAY_TYPE* screen) {
	std::vector<std::string> dates;
	std::vector<std::string> times;
	std::string category = "";
	std::string priority = "";
	string description = "";
	flagArg(parameter);
	int wordReading = parameterNum - 1;
	if(_parser.isCategory(parameters.back())){
		category=_parser.replaceWord("#","",parameters.back());
		parameters.pop_back();
	}
	if(_parser.isPriority(parameters.back())){
		priority=_parser.replaceWord("!","",parameters.back());
		parameters.pop_back();
	}

	while(!parameters.empty()){
		if(_parser.isTimeFormat(parameters.back())){
			times.push_back(parameters.back());
			parameters.pop_back();
			if(parameters.size()!=0 && _parser.isPreposition(parameters.back())){
				parameters.pop_back();
			}
		}else if(_parser.isDateFormat(parameters.back())){
			dates.push_back(parameters.back());
			parameters.pop_back();
			if(parameters.size()!=0 && _parser.isPreposition(parameters.back())){
				parameters.pop_back();
			}
		}else{
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
		if(priority=="H" || priority=="high") {
			commandAdd->setPriority(HIGH);
		} else if(priority=="M" || priority=="medium") {
			commandAdd->setPriority(MEDIUM);
		} else if(priority=="L" || priority=="low") {
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
		switch(times.size()){
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
	commandAdd->setPreviousScreen(screen);
	return commandAdd;
}

	

	
Command* CommandCreator::createCommandDelete(std::string parameter,DISPLAY_TYPE* type) {
	if(_parser.isAllNumbers(parameter)) {
		unsigned int id = _parser.toNum(parameter) - 1;
		flagIndex(id);
		Command_Delete* commandDelete = new Command_Delete;
		commandDelete->setDeletionIndex(id);
		commandDelete->setDisplayScreen(*type);
		return commandDelete;
	} else {
		throw NotANumberException();
		return NULL;
	}

}

Command* CommandCreator::createCommandEdit(vector<std::string> parameters,DISPLAY_TYPE* type){
	Command_Edit* commandEdit = new Command_Edit;

	commandEdit->setIndex(_parser.toNum(parameters[0])-1);
	string header = parameters[1];
	int contentStartPoint = 2;
	if(header=="start" || header=="due") {
		header += parameters[2];
		contentStartPoint = 3;
	}
	string content = "";
	for(int i=0 ; (i+contentStartPoint)<parameters.size() ; i++) {
		if(i) {
			content += " ";
		}
		content += parameters[contentStartPoint+i];
	}

	commandEdit->setHeader(header);

	if(header=="description") {
		commandEdit->setDescription(content);
	} else if(header=="startDate") {
		int dateInt = _parser.toNum(_parser.replaceWord("/","",content));
		commandEdit->setStartDate(Date((dateInt/1000000),(dateInt/10000)%100,dateInt%10000));
	} else if(header=="startTime") {
		int timeInt = _parser.toNum(_parser.replaceWord("/","",content));
		commandEdit->setStartTime(ClockTime(timeInt));
	} else if(header=="dueDate") {
		int dateInt = _parser.toNum(_parser.replaceWord("/","",content));
		commandEdit->setEndDate(Date((dateInt/1000000),(dateInt/10000)%100,dateInt%10000));
	} else if(header=="dueTime") {
		int timeInt = _parser.toNum(_parser.replaceWord("/","",content));
		commandEdit->setEndTime(ClockTime(timeInt));
	} else if(header=="category") {
		commandEdit->setCategory(content);
	} else if(header=="priority") {
		content = _parser.replaceWord("!", "", content);
		if(content=="H" || content=="high") {
			commandEdit->setPriority(HIGH);
		} else if(content=="M" || content=="medium") {
			commandEdit->setPriority(MEDIUM);
		} else if(content=="L" || content=="low") {
			commandEdit->setPriority(LOW);
		}
	}
	commandEdit->setDisplayScreen(*type);
	return commandEdit;
}


Command* CommandCreator::createCommandDone(std::string parameter,DISPLAY_TYPE* type){
	if(_parser.isAllNumbers(parameter)) {
		unsigned int id = _parser.toNum(parameter) - 1;
		flagIndex(id);
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
		unsigned int id = _parser.toNum(parameter) - 1;
		flagIndex(id);
		Command_Undone* commandUndone = new Command_Undone;
		commandUndone->setUncompletedIndex(id);
		commandUndone->setDisplayScreen(*type);
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
	std::string feedback = "";
	for (int i = 0; i < _feedbackExceptiontoUI.size(); i++) {
		feedback += _feedbackExceptiontoUI[i] + "\n";
	}
	return feedback;
}

Command* CommandCreator::createCommandDisplay(string parameter, DISPLAY_TYPE* displayType)
{
	Command_Display* newCommand= new Command_Display();
	newCommand->setPreviousScreen(displayType);
	if(parameter=="main"){
		newCommand->setNextScreen(MAIN);
	}else if(parameter=="overdue"){
		newCommand->setNextScreen(LATE);
	}else if(parameter=="completed"){
		newCommand->setNextScreen(COMPLETE);
	}else{
		delete newCommand;
		newCommand==NULL;
		throw InvalidAddCommandInputException();
	}
	return newCommand;
}

