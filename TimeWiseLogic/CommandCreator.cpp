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
Command* CommandCreator::interpretCommand(std::string userInput) {
	try {
	string commandTypeString = _parser.getFirstWord(userInput);
	CMD_TYPE commandType = _parser.determineCommandType(commandTypeString);
	
		string parameter = _parser.removeFirstWord(userInput);
		vector<string> parameters = _parser.splitBySpace(parameter);
		unsigned int parameterNum = parameters.size();
		switch (commandType) {
			case ADD: {
				return createCommandAdd(parameter,parameterNum,parameters);
			}
			
			case DELETE: {
				return createCommandDelete(parameter);
			}
			case EDIT: {
				return createCommandEdit(parameters);
			}
			case DONE: {
				return createCommandDone(parameter);
			}
			case UNDONE: {
				return createCommandUndone(parameter);
			}
			case CLEAR: {
				return createCommandClear();
			}
			case UNDO: {
				return createCommandUndo();
			}
			case REDO: {
				return createCommandRedo();
			}
			case SEARCH: {
				return createCommandSearch(parameter);
			}
			default: {
				throw InvalidCommandWordException();
				return NULL;
			}
		}
	} catch (InvalidCommandWordException& icwe) {
		_feedbackExceptiontoUI.push_back(icwe.what());
	} catch (NoArgumentException& nae) {
		_feedbackExceptiontoUI.push_back(nae.what());
	} catch (InvalidAddCommandInputException& iacie) {
		_feedbackExceptiontoUI.push_back(iacie.what());
	} catch (OutOfRangeException& oore) {
		_feedbackExceptiontoUI.push_back(oore.what());
	} catch (NotANumberException& nane) {
		_feedbackExceptiontoUI.push_back(nane.what());
	}

}

Command* CommandCreator::createCommandAdd(std::string parameter, unsigned int parameterNum, vector<std::string> parameters ) {
	Command_Add* commandAdd = new Command_Add;
	flagArg(parameter);
	int wordReading = parameterNum - 1;

	// Get category from user command
	std::string category = "";
	if(wordReading>=0 && parameters[wordReading][0]=='#') {
		category =_parser.replaceWord("#","",parameters[wordReading--]);
	}

	// Get priority from user command
	std::string priority = "";
	if(wordReading>=0 && parameters[wordReading][0]=='!') {
		priority = _parser.replaceWord("!","",parameters[wordReading--]);

	}

	// Get time from user command
	string time = "";
	if(wordReading >= 0 && _parser.isTimeFormat(parameters[wordReading])) {
		time = parameters[wordReading--];
		if( wordReading >= 0 && _parser.isPreposition(parameters[wordReading])) {
			wordReading--;
		}
	}

	// Get date from user command
	string date = "";
	if(wordReading >=0 && _parser.isDateFormat(parameters[wordReading])) {
		date = parameters[wordReading--];
		if(wordReading>=0 && _parser.isPreposition(parameters[wordReading])) {
			wordReading--;
		}
	}

	// Get description
	string description = "";
	for(int i=0 ; i<=wordReading; i++) {
		if(i) {
			description += " ";
		}
		description += parameters[i];
	}
	flagDescription(description);
	// Set the commandAdd
	time = _parser.replaceWord(":","",time);

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

	if(date!="") {
		commandAdd->setEndDate(*_parser.createDate(date));
	}

	if(time != "") {
		commandAdd->setEndTime(*_parser.createTime(time));
	}
	return commandAdd;
}

	

	
Command* CommandCreator::createCommandDelete(std::string parameter) {
	if(_parser.isAllNumbers(parameter)) {
		Command_Delete* commandDelete = new Command_Delete;
		unsigned int id = _parser.toNum(parameter) - 1;
		flagIndex(id);
		commandDelete->setDeletionIndex(id);
		return commandDelete;
	} else {
		throw NotANumberException();
		return NULL;
	}

}

Command* CommandCreator::createCommandEdit(vector<std::string> parameters){
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
	return commandEdit;
}


Command* CommandCreator::createCommandDone(std::string parameter){
	if(_parser.isAllNumbers(parameter)) {
		Command_Done* commandDone = new Command_Done;
		unsigned int id = _parser.toNum(parameter) - 1;
		flagIndex(id);
		commandDone->setCompletedIndex(id);
		return commandDone;
	} else {
		throw NotANumberException();
		return NULL;
	} 
}

Command* CommandCreator::createCommandUndone(std::string parameter){
	if(_parser.isAllNumbers(parameter)) {
		Command_Undone* commandUndone = new Command_Undone;
		unsigned int id = _parser.toNum(parameter) - 1;
		flagIndex(id);
		commandUndone->setUncompletedIndex(id);
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

Command* CommandCreator::createCommandClear(){
	Command_Clear* newCommand = new Command_Clear;
	return newCommand;
}

Command* CommandCreator::createCommandSearch(std::string parameter){
	Command_Search* commandSearch = new Command_Search;
	flagArg(parameter);
	commandSearch->setKeyword(parameter);
	return commandSearch;
}

std::string CommandCreator::getFeedback() {
	std::string feedback = "";
	for (int i = 0; i < _feedbackExceptiontoUI.size(); i++) {
		feedback += _feedbackExceptiontoUI[i] + "\n";
	}
	return feedback;
}

	
/*
std::string Parser::getFeedback() {
	string feedback = "";
	for ( int i = 0; i < _feedbackExceptiontoUI.size(); i++) {
		feedback += _feedbackExceptiontoUI[i] + "\n";
	}
	return feedback;
}



	try {
		string commandTypeString = getFirstWord(action);
		CMD_TYPE commandType = determineCommandType(commandTypeString);
	
		string parameter = removeFirstWord(action);
		vector<string> parameters = splitBySpace(parameter);
		unsigned int parameterNum = parameters.size();

		switch (commandType) {	
			case ADD: {
				try {
					
				
					  
			case DELETE:
				try {
					if(isAllNumbers(parameter)) {
						Command_Delete* commandDelete = new Command_Delete;
						unsigned int id = toNum(parameter) - 1;
						flagIndex(id);
						commandDelete->setDeletionIndex(id);
						return commandDelete;
					} else {
						return NULL;
					}
				} catch (OutOfRangeException& ooe) {
					_feedbackExceptiontoUI.push_back(ooe.what());
				} catch (NotANumberException& nane) {
					_feedbackExceptiontoUI.push_back(nane.what());
				} catch (NoArgumentException& nae) {
					_feedbackExceptiontoUI.push_back(nae.what());
				}
			case DONE:
				try {
					if(isAllNumbers(parameter)) {
					Command_Done* commandDone = new Command_Done;
					unsigned int id = toNum(parameter) - 1;
					commandDone->setCompletedIndex(id);
					} else {
					return NULL;
					}
				} catch (NotANumberException& nane) {
					_feedbackExceptiontoUI.push_back(nane.what());
				} catch (NoArgumentException& nae) {
					_feedbackExceptiontoUI.push_back(nae.what());
				} catch (OutOfRangeException& oore) {
					_feedbackExceptiontoUI.push_back(oore.what());
				}

			case UNDONE:
				try {
					if(isAllNumbers(parameter)) {
					Command_Undone* commandUndone = new Command_Undone;
					unsigned int id = toNum(parameter) - 1;
					commandUndone->setUncompletedIndex(id);
					} else {
					return NULL;
					}
				} catch (NotANumberException& nane) {
					_feedbackExceptiontoUI.push_back(nane.what());
				} catch (NoArgumentException& nae) {
					_feedbackExceptiontoUI.push_back(nae.what());
				} catch (OutOfRangeException& oore) {
					_feedbackExceptiontoUI.push_back(oore.what());
				}
			case SEARCH: 
				try {
					Command_Search* commandSearch = new Command_Search;
					flagArg(parameter);
					commandSearch->setKeyword(parameter);
					return commandSearch;
				} catch (NoArgumentException& nae) {
					_feedbackExceptiontoUI.push_back(nae.what());
				}

			case CLEAR: {
				Command_Clear* newCommand= new Command_Clear;
				return newCommand;
				}
			case UNDO: {
				Command_Undo* newCommand= new Command_Undo;
				return newCommand;
					   }
			case REDO: {
				Command_Redo* newCommand= new Command_Redo;
				return newCommand;
					   }
			case EDIT: {
				Command_Edit* commandEdit = new Command_Edit;

				commandEdit->setIndex(toNum(parameters[0])-1);
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
					int dateInt = toNum(replaceWord("/","",content));
					commandEdit->setStartDate(Date((dateInt/1000000),(dateInt/10000)%100,dateInt%10000));
				} else if(header=="startTime") {
					int timeInt = toNum(replaceWord("/","",content));
					commandEdit->setStartTime(ClockTime(timeInt));
				} else if(header=="dueDate") {
					int dateInt = toNum(replaceWord("/","",content));
					commandEdit->setEndDate(Date((dateInt/1000000),(dateInt/10000)%100,dateInt%10000));
				} else if(header=="dueTime") {
					int timeInt = toNum(replaceWord("/","",content));
					commandEdit->setEndTime(ClockTime(timeInt));
				} else if(header=="category") {
					commandEdit->setCategory(content);
				} else if(header=="priority") {
					content = replaceWord("!", "", content);
					if(content=="H" || content=="high") {
						commandEdit->setPriority(HIGH);
					} else if(content=="M" || content=="medium") {
						commandEdit->setPriority(MEDIUM);
					} else if(content=="L" || content=="low") {
						commandEdit->setPriority(LOW);
					}
				}
				return commandEdit;
				}
			default:
				return NULL;
			}
		} catch (InvalidCommandWordException& icwe) {
		string exception = icwe.what();
		_feedbackExceptiontoUI.push_back(exception);
	}
		
}
*/