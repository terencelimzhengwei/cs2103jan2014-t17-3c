#include "Storage.h"


Storage::Storage(void) {
	_undoneFileName = "undoneTasks.txt";
	_doneFileName = "doneTasks.txt";

}

Storage::~Storage(void)
{
}

void Storage::saveFile(TaskList& listOfTasks){ 
	saveUndoneTasks(listOfTasks);
	saveDoneTasks(listOfTasks);
}

void Storage::retrieveFile(TaskList& listOfTasks) { 
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
		writeFile<<"\n"<< "Priority: " << PRIORITY_STRING[listOfTasks.getTask(i)->getPriority()] << "\n"
			<< "Category: " << listOfTasks.getTask(i)->getTaskCategory() << "\n"
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
		writeFile<<"\n"<< "Priority: " << PRIORITY_STRING[listOfTasks.getCompletedTask(i)->getPriority()] << "\n"
			<< "Category: " << listOfTasks.getCompletedTask(i)->getTaskCategory() << "\n"
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
						newTask->setStartDate(*_parser.createDate(details));
					}break;
				case 2:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						newTask->setEndDate(*_parser.createDate(details));
					}break;
				case 3:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						newTask->setStartTime(*_parser.createTime(details));
					}break;
				case 4:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						newTask->setEndTime(*_parser.createTime(details));
					}break;
				case 5:
					taskHeader++;
					newTask->setPriority(_parser.getPriority(details));
					break;
				case 6:
					taskHeader++;
					newTask->setCategory(details);
					break;
				case 7:
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
					}else{
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

void Storage::retrieveUndoneTasks(TaskList& listOfTasks){
	std::string userInput="";
	std::ifstream input(_undoneFileName);
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
						newTask->setStartDate(*_parser.createDate(details));
					}break;
				case 2:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						newTask->setEndDate(*_parser.createDate(details));
					}break;
				case 3:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						newTask->setStartTime(*_parser.createTime(details));
					}break;
				case 4:
					taskHeader++;
					if(details==""||details==" "){
						break;
					}else{
						newTask->setEndTime(*_parser.createTime(details));
					}break;
				case 5:
					taskHeader++;
					newTask->setPriority(_parser.getPriority(details));
					break;
				case 6:
					taskHeader++;
					newTask->setCategory(details);
					break;
				case 7:
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
					}else{
						break;
					}
				}

				getline(input, userInput);
			} 
			listOfTasks.addTask(*newTask);
		} 
	}

	input.close();
}
