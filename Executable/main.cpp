#include "TimeWiseLogic.h"
#include <iostream>

int main(){
	TimeWiseLogic logic;
	logic.processCommand("add motherfucker");
	TaskList tasklist = logic.getTaskList();
	Task task=tasklist.getTask(0);
	std::cout<<task.getDescription()<<endl;

	system("pause");
	return 0;
}