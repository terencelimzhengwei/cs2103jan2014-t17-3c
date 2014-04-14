//@author A0097330H
#include "Storage.h"

Storage::Storage(void) {
	_logger = Logger::getLogger();
	_undoneFileName = UNDONE_TASK_TEXTFILE;
	_doneFileName = DONE_TASK_TEXTFILE;
}

Storage::~Storage(void) {
}

void Storage::saveFile(TaskList& listOfTasks) { 
	_logger->log(LOG_MESSAGE_STORAGE, LOG_MESSAGE_SAVING);
	saveUndoneTasks(listOfTasks);
	saveDoneTasks(listOfTasks);
}

void Storage::retrieveFile(TaskList& listOfTasks) { 
	_logger->log(LOG_MESSAGE_STORAGE, LOG_MESSAGE_RETRIEVAL);
	retrieveUndoneTasks(listOfTasks);
	retrieveDoneTasks(listOfTasks);
}

void Storage::saveUndoneTasks(TaskList& listOfTasks) {
	std::ofstream writeFile(_undoneFileName);
	for(unsigned int i = 0; i < listOfTasks.undoneSize(); i++) { 
		writeFile << DESCRIPTION_FIELD << listOfTasks.getTask(i)->getDescription();
		writeFile << NEW_LINE << START_DATE_FIELD;
		if(listOfTasks.getTask(i)->getStartDate() != NULL) {
			writeFile<< listOfTasks.getTask(i)->getStartDate()->toFormat();
		}
		writeFile << NEW_LINE << END_DATE_FIELD;
		if(listOfTasks.getTask(i)->getEndDate() != NULL) {
			writeFile << listOfTasks.getTask(i)->getEndDate()->toFormat();
		}
		writeFile << NEW_LINE << START_TIME_FIELD;
		if(listOfTasks.getTask(i)->getStartTime() != NULL) {
			writeFile << listOfTasks.getTask(i)->getStartTime()->toString();
		}
		writeFile << NEW_LINE << END_TIME_FIELD;
		if(listOfTasks.getTask(i)->getEndTime() != NULL) {
			writeFile << listOfTasks.getTask(i)->getEndTime()->toString();
		}
		writeFile << NEW_LINE
			<< CATEGORY_FIELD << listOfTasks.getTask(i)->getTaskCategory()
			<< NEW_LINE
			<< STATUS_FIELD << TASK_STATUS_STRING[listOfTasks.getTask(i)->getTaskStatus()] 
			<< NEW_LINE;

		writeFile << SEPARATOR;
		if(i != listOfTasks.undoneSize() - REDUCTION_VALUE) {
			writeFile << std::endl;
		}
	} 
}

void Storage::saveDoneTasks(TaskList& listOfTasks){
	std::ofstream writeFile(_doneFileName);
	for(unsigned int i = 0; i < listOfTasks.doneSize(); i++) { 
		writeFile << DESCRIPTION_FIELD << listOfTasks.getCompletedTask(i)->getDescription();
		writeFile  << NEW_LINE << START_DATE_FIELD;
		if(listOfTasks.getCompletedTask(i)->getStartDate() != NULL){
			writeFile << listOfTasks.getCompletedTask(i)->getStartDate()->toFormat();
		}
		writeFile << NEW_LINE << END_DATE_FIELD;
		if(listOfTasks.getCompletedTask(i)->getEndDate() != NULL){
			writeFile << listOfTasks.getCompletedTask(i)->getEndDate()->toFormat();
		}
		writeFile << NEW_LINE <<  START_TIME_FIELD;
		if(listOfTasks.getCompletedTask(i)->getStartTime() != NULL){
			writeFile << listOfTasks.getCompletedTask(i)->getStartTime()->toString();
		}
		writeFile << NEW_LINE << END_TIME_FIELD;
		if(listOfTasks.getCompletedTask(i)->getEndTime() != NULL){
			writeFile << listOfTasks.getCompletedTask(i)->getEndTime()->toString();
		}
		writeFile << NEW_LINE 
			<< CATEGORY_FIELD << listOfTasks.getCompletedTask(i)->getTaskCategory() 
			<< NEW_LINE
			<< "Status: " << TASK_STATUS_STRING[listOfTasks.getCompletedTask(i)->getTaskStatus()] 
			<< NEW_LINE;
		
		writeFile << SEPARATOR;
		if(i != listOfTasks.undoneSize() - REDUCTION_VALUE) {
			writeFile << std::endl;
		}
	} 
}

//Retrieves information of done tasks.
void Storage::retrieveDoneTasks(TaskList& listOfTasks) {
	std::string userInput = DEFAULT_EMPTY;
	std::ifstream input(_doneFileName);
	std::string temp;
	int taskHeader;

	if(input.is_open()) {
		while(!input.eof()) {
			taskHeader = START_VALUE;
			getline(input,userInput);
			if(userInput == DEFAULT_EMPTY) {
				return;
			}
			Task* newTask = new Task;
			while (userInput != SEPARATOR) {
				std::string details = Parser::removeFirstWord(userInput);
				details = Parser::trim(details);
				switch(taskHeader) {
				case HEADER_DESCRIPTION: {
					newTask->setDescription(details);
					taskHeader++;
					break;
				}
				case HEADER_START_DATE: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try{
							newTask->setStartDate(_parser.createDate(details));
						} catch(...) {
							delete newTask->getStartDate();
							newTask->setStartDate(NULL);
							_corrupted=true;
						}
					}
					break;
				}
				case HEADER_END_DATE: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setEndDate(_parser.createDate(details));
						} catch(...) {
							delete newTask->getEndDate();
							newTask->setEndDate(NULL);
							_corrupted=true;
						}					
					} break;
				}
				case HEADER_START_TIME: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setStartTime(_parser.createTime(details));
						} catch(...) {
							delete newTask->getStartTime();
							newTask->setStartTime(NULL);
							_corrupted=true;
						}						
					}
					break;
				}
				case HEADER_END_TIME: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setEndTime(_parser.createTime(details));
						} catch(...) {
							delete newTask->getEndTime();
							newTask->setEndTime(NULL);
							_corrupted=true;
						}						
					} 
					break;
				}
				case HEADER_CATEGORY: {
					taskHeader++;
					newTask->setCategory(details);
					break;
				}
				case HEADER_STATUS: {
					taskHeader++;
					TASK_STATUS status = _parser.getTaskStatus(details);
					newTask->setStatusAsDone();
					break;
				}
				}
				getline(input, userInput);
			} 
			listOfTasks.addTaskToDoneList(*newTask);
		} 
	}
	input.close();
}

//Retrieves information of uncompleted tasks.
void Storage::retrieveUndoneTasks(TaskList& listOfTasks) {
	std::string userInput = DEFAULT_EMPTY;
	std::ifstream input(_undoneFileName);
	std::string temp;
	int taskHeader;

	if(input.is_open()) {
		while(!input.eof()) {
			taskHeader = START_VALUE;
			getline(input,userInput);
			if(userInput == DEFAULT_EMPTY) {
				return;
			}
			Task* newTask = new Task;

			while (userInput != SEPARATOR) {
				std::string details = _parser.removeFirstWord(userInput);
				details = Parser::trim(details);

				switch(taskHeader){
				case HEADER_DESCRIPTION : {
					newTask->setDescription(details);
					taskHeader++;
					break;
				}
				case HEADER_START_DATE: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setStartDate(_parser.createDate(details));
						} catch(...) {
							delete newTask->getStartDate();
							newTask->setStartDate(NULL);
							_corrupted=true;
						}
					}
					break;
				}
				case HEADER_END_DATE: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setEndDate(_parser.createDate(details));
						} catch(...) {
							delete newTask->getEndDate();
							newTask->setEndDate(NULL);
							_corrupted=true;
						}					
					}
					break;
				}
				case HEADER_START_TIME: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setStartTime(_parser.createTime(details));
						} catch(...) {
							delete newTask->getStartTime();
							newTask->setStartTime(NULL);
							_corrupted=true;
						}						
					}
					break;
				}
				case HEADER_END_TIME: {
					taskHeader++;
					if(details == DEFAULT_EMPTY || details == SPACE_PARAMETER) {
						break;
					} else {
						try {
							newTask->setEndTime(_parser.createTime(details));
						} catch(...) {
							delete newTask->getEndTime();
							newTask->setEndTime(NULL);
							_corrupted=true;
						}						
					}
					break;
				}
				case HEADER_CATEGORY: {
					taskHeader++;
					newTask->setCategory(details);
					break;
				}
				case HEADER_STATUS: {
					taskHeader++;
					TASK_STATUS status =_parser.getTaskStatus(details);
					if(status == DONE) {
						newTask->setStatusAsDone();
						break;
					} else if(status == UNCOMPLETED) {
						newTask->setStatusasUndone();
						break;
					} else if(status == OVERDUE) {
						newTask->setStatusAsOverdue();
						break;
					} else {
						_corrupted = true;
						break;
					}
				}
				default:
					_corrupted = true;
				}
				if(taskHeader > COLUMN_OUT_OF_BOUND) {
					break;
				}
				getline(input, userInput);
			} 
			listOfTasks.addTask(*newTask);
		} 
	}
	input.close();
}
