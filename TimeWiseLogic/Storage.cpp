#include "Storage.h"


Storage::Storage(void) {
	_fileName = "Storage.txt";
}

Storage::~Storage(void)
{
}

void Storage::saveFile(TaskList& listOfTasks){ 
	std::ofstream writeFile(_fileName);
	for(int i = 0; i < listOfTasks.size(); i++) { 
		writeFile << "Description: " << listOfTasks.getTask(i)->getDescription() << "\n";
		writeFile << "Start_Date: ";
		if(listOfTasks.getTask(i)->getStartDate()!=NULL){
			writeFile<< listOfTasks.getTask(i)->getStartDate()->toSaveFormat();
		}

		writeFile <<"\n"<< "End_Date: ";
		if(listOfTasks.getTask(i)->getEndDate()!=NULL){
			writeFile<< listOfTasks.getTask(i)->getEndDate()->toSaveFormat();
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
		if(i==listOfTasks.size()-1){
			writeFile<< "==========";
		}else{
			writeFile<< "=========="<<std::endl;
		}
	} 
}

void Storage::retrieveFile(TaskList& listOfTasks) { 
	std::string userInput="";
	std::ifstream input(_fileName);
	std::string temp;
	int taskHeader;

	if(input.is_open()) {
		while(!input.eof()) {
			taskHeader=0;
			getline(input,userInput);
			Task* newTask = new Task;
			while (userInput != "==========") {
				std::string details = _parser.removeFirstWord(userInput); 
				switch(taskHeader){
				case 0 :
					newTask->setDescription(details);
					taskHeader++;
					break;
				case 1:
					taskHeader++;
					if(details!=""||details!=" "){
						break;
					}else{
						newTask->setStartDate(*_parser.createDate(details));
					}break;
				case 2:
					taskHeader++;
					if(details!=""||details!=" "){
						break;
					}else{
						newTask->setEndDate(*_parser.createDate(details));
					}break;
				case 3:
					taskHeader++;
					if(details!=""||details!=" "){
						break;
					}else{
						newTask->setStartTime(*_parser.createTime(details));
					}break;
				case 4:
					taskHeader++;
					if(details!=""||details!=" "){
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