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
		writeFile << "Description: " << listOfTasks.getTask(i)->getDescription() << "\n" 
			<< "Start_Date: " << listOfTasks.getTask(i)->getStartDate() << "\n"
			<< "End_Date: " << listOfTasks.getTask(i)->getEndDate() << "\n"
			<< "Start_Time: " << listOfTasks.getTask(i)->getStartTime() << "\n"
			<< "End_Time: " << listOfTasks.getTask(i)->getEndTime() << "\n"
			<< "Priority: " << listOfTasks.getTask(i)->getPriority() << "\n"
			<< "Category: " << listOfTasks.getTask(i)->getTaskCategory() << "\n"
			<< "Status: " << listOfTasks.getTask(i)->getTaskStatus() << "\n"
			<< "==========" << std::endl;
	} 
}

void Storage::retrieveFile(TaskList& listOfTasks) { 
	std::string userInput;
	std::ifstream input(_fileName);

	if(input.is_open()) {
		while(!input.eof()) {
			getline(input,userInput);
			std::ostringstream outstr;
			while (userInput != "==========") {
				std::string details = removeFirstWord(userInput); 
				
				outstr << details << "";
				
				getline(input, userInput);
			} 
			std::string entireTask = outstr.str();
			_parser.interpretCommand(entireTask);
		} 
	}
	
	input.close();
}

std::string Storage::removeFirstWord(std::string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tStart = action.find_first_of(" ") + 1;
	tEnd = action.size();

	std::string userText = action.substr(tStart, tEnd - tStart);
	return userText;
}
