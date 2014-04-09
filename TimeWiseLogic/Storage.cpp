#include "Storage.h"


Storage::Storage(void) {
	_logger = Logger::getLogger();
	_undoneFileName = "undoneTasks.txt";
	_doneFileName = "doneTasks.txt";

}

Storage::~Storage(void)
{
}

void Storage::saveFile(TaskList& listOfTasks){ 
	_logger->log("Storage","Saving Tasks to Text file");
	saveUndoneTasks(listOfTasks);
	saveDoneTasks(listOfTasks);
}

void Storage::retrieveFile(TaskList& listOfTasks) { 
	_logger->log("Storage","Retrieving Tasks from Text file");
	retrieveUndoneTasks(listOfTasks);
	retrieveDoneTasks(listOfTasks);
}

void Storage::saveUndoneTasks(TaskList& listOfTasks){
	std::ofstream writeFile(_undoneFileName);
	for(int i = 0; i < listOfTasks.undoneSize(); i++) { 
		writeFile << "Description: " << listOfTasks.getTask(i)->getDescription() << "\n";
		writeFile << "Start_Date: ";
		if(listOfTasks.getTask(i)->getStartDate()!=NULL){
			writeFile<< listOfTasks.getTask(i)->getStartDate()->toFormat();
		}

		writeFile <<"\n"<< "End_Date: ";
		if(listOfTasks.getTask(i)->getEndDate()!=NULL){
			writeFile<< listOfTasks.getTask(i)->getEndDate()->toFormat();
		}
		writeFile <<"\n"<< "Start_Time: ";
		if(listOfTasks.getTask(i)->getStartTime()!=NULL){
			writeFile<< listOfTasks.getTask(i)->getStartTime()->toString();
		}
		writeFile<<"\n"<< "End_Time: ";
		if(listOfTasks.getTask(i)->getEndTime()!=NULL){
			writeFile<< listOfTasks.getTask(i)->getEndTime()->toString();
		}
		writeFile<<"\n"<< "Category: " << listOfTasks.getTask(i)->getTaskCategory() << "\n"
			<< "Status: " << TASK_STATUS_STRING[listOfTasks.getTask(i)->getTaskStatus()] << "\n";
		if(i==listOfTasks.undoneSize()-1){
			writeFile<< "==========";
		}else{
			writeFile<< "=========="<<std::endl;
		}
	} 
}

void Storage::saveDoneTasks(TaskList& listOfTasks){
	std::ofstream writeFile(_doneFileName);
	for(int i = 0; i < listOfTasks.doneSize(); i++) { 
		writeFile << "Description: " << listOfTasks.getCompletedTask(i)->getDescription() << "\n";
		writeFile << "Start_Date: ";
		if(listOfTasks.getCompletedTask(i)->getStartDate()!=NULL){
			writeFile<< listOfTasks.getCompletedTask(i)->getStartDate()->toFormat();
		}

		writeFile <<"\n"<< "End_Date: ";
		if(listOfTasks.getCompletedTask(i)->getEndDate()!=NULL){
			writeFile<< listOfTasks.getCompletedTask(i)->getEndDate()->toFormat();
		}
		writeFile <<"\n"<< "Start_Time: ";
		if(listOfTasks.getCompletedTask(i)->getStartTime()!=NULL){
			writeFile<< listOfTasks.getCompletedTask(i)->getStartTime()->toString();
		}
		writeFile<<"\n"<< "End_Time: ";
		if(listOfTasks.getCompletedTask(i)->getEndTime()!=NULL){
			writeFile<< listOfTasks.getCompletedTask(i)->getEndTime()->toString();
		}
		writeFile<<"\n"<<"Category: " << listOfTasks.getCompletedTask(i)->getTaskCategory() << "\n"
			<< "Status: " << TASK_STATUS_STRING[listOfTasks.getCompletedTask(i)->getTaskStatus()] << "\n";
		if(i==listOfTasks.undoneSize()-1){
			writeFile<< "==========";
		}else{
			writeFile<< "=========="<<std::endl;
		}
	} 
}

void Storage::retrieveDoneTasks(TaskList& listOfTasks){
	std::string userInput="";
	std::ifstream input(_doneFileName);
	std::string temp;
	int taskHeader;

	if(input.is_open()) {
		while(!input.eof()) {
			taskHeader=0;
			getline(input,userInput);
			if(userInput==""){
				return;
			}
			Task* newTask = new Task;
			while (userInput != "==========") {
				std::string details = _parser.removeFirstWord(userInput);
				_parser.removeWhiteSpaces(details);
				switch(taskHeader){
				case 0 :
					newTask->setDescription(details);
					taskHeader++;
					break;
				case 1:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setStartDate(_parser.createDate(details));
						}catch(...){
							delete newTask->getStartDate();
							newTask->setStartDate(NULL);
							_corrupted=true;
						}
					}break;
				case 2:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setEndDate(_parser.createDate(details));
						}catch(...){
							delete newTask->getEndDate();
							newTask->setEndDate(NULL);
							_corrupted=true;
						}					
					}break;
				case 3:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setStartTime(_parser.createTime(details));
						}catch(...){
							delete newTask->getStartTime();
							newTask->setStartTime(NULL);
							_corrupted=true;
						}						
					}break;
				case 4:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setEndTime(_parser.createTime(details));
						}catch(...){
							delete newTask->getEndTime();
							newTask->setEndTime(NULL);
							_corrupted=true;
						}						
					}break;
				case 5:
					taskHeader++;
					newTask->setCategory(details);
					break;
				case 6:
					taskHeader++;
					TASK_STATUS status=_parser.getTaskStatus(details);
					newTask->setStatusAsDone();
				}
				getline(input, userInput);
			} 
			listOfTasks.addTaskToDoneList(*newTask);
		} 
	}

	input.close();
}

void Storage::retrieveUndoneTasks(TaskList& listOfTasks){
	std::string userInput="";
	std::ifstream input(_undoneFileName);
	int checkClash;
	std::string temp;
	int taskHeader;

	if(input.is_open()) {
		while(!input.eof()) {
			taskHeader=0;
			getline(input,userInput);
			if(userInput==""){
				return;
			}
			Task* newTask = new Task;

			while (userInput != "==========") {
				std::string details = _parser.removeFirstWord(userInput);
				_parser.removeWhiteSpaces(details);

				switch(taskHeader){
				case 0 :
					newTask->setDescription(details);
					taskHeader++;
					break;
				case 1:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setStartDate(_parser.createDate(details));
						}catch(...){
							delete newTask->getStartDate();
							newTask->setStartDate(NULL);
							_corrupted=true;
						}
					}break;
				case 2:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setEndDate(_parser.createDate(details));
						}catch(...){
							delete newTask->getEndDate();
							newTask->setEndDate(NULL);
							_corrupted=true;
						}					
					}break;
				case 3:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setStartTime(_parser.createTime(details));
						}catch(...){
							delete newTask->getStartTime();
							newTask->setStartTime(NULL);
							_corrupted=true;
						}						
					}break;
				case 4:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						try{
							newTask->setEndTime(_parser.createTime(details));
						}catch(...){
							delete newTask->getEndTime();
							newTask->setEndTime(NULL);
							_corrupted=true;
						}						
					}break;
				case 5:
					taskHeader++;
					newTask->setCategory(details);
					break;
				case 6:{
					taskHeader++;
					TASK_STATUS status=_parser.getTaskStatus(details);
					if(status==DONE){
						newTask->setStatusAsDone();
						break;
					}else if(status==UNCOMPLETED){
						newTask->setStatusasUndone();
						break;
					}else if(status==OVERDUE){
						newTask->setStatusAsOverdue();
						break;
					}else {
						_corrupted=true;
						break;
					}
				}
				default:
					_corrupted=true;
				}
				if(taskHeader>8){
					break;
				}
				getline(input, userInput);
			} 
			listOfTasks.addTask(*newTask, checkClash);
		} 
	}

	input.close();
}
