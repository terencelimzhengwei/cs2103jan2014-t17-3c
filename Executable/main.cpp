#include "TimeWiseLogic.h"
#include <iostream>

int main(){
	TimeWiseLogic logic;
	std::string feedback;
	feedback= logic.processCommand("add testing only");
	cout<<feedback<<endl;
	TaskList& taskList = logic.getTaskList();
	std::string taskDescription = (taskList.getTask(0)).getDescription();
	cout<<taskDescription<<endl;

	system("pause");
	return 0;
}