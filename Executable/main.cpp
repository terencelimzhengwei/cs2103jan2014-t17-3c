#include "TimeWiseLogic.h"
#include <iostream>

int main(){
	/*TimeWiseLogic _logic;
	std::string input;
	TaskList& _tasklist = _logic.getTaskList();

	while(true){
		getline(cin,input);
		_logic.processCommand(input);
		_tasklist=_logic.getTaskList();
		for(int i=0;i<_tasklist.size();i++){
			cout<<"Description: "<<_tasklist.getTask(i)->getDescription()<<endl;
			if(_tasklist.getTask(i)->getStartDate()!=NULL){
				cout<<"SD: "<<_tasklist.getTask(i)->getStartDate()->toString()<<endl;
			}if(_tasklist.getTask(i)->getEndDate()!=NULL){
				cout<<"ED: "<<_tasklist.getTask(i)->getEndDate()->toString()<<endl;
			}if(_tasklist.getTask(i)->getStartTime()!=NULL){
				cout<<"ST: "<<_tasklist.getTask(i)->getStartTime()->toString()<<endl;
			}if(_tasklist.getTask(i)->getEndTime()!=NULL){
				cout<<"ET: "<<_tasklist.getTask(i)->getEndTime()->toString()<<endl;
			}if(_tasklist.getTask(i)->getPriority()!=DEFAULT_PRIORITY){
				cout<<"Pri: "<<PRIORITY_STRING[_tasklist.getTask(i)->getPriority()]<<endl;
			}
			cout<<"cat: "<<_tasklist.getTask(i)->getTaskCategory()<<endl;
		}
	}*/

	TaskList _taskList;
	std::vector<Command_Add*> commandToBeExecuted;
	ClockTime startTime(1200);
	ClockTime endTime(1600);
	Date startDate(10,3,2014);
	Date endDate(12,3,2014);
	commandToBeExecuted.push_back(new Command_Add);
	commandToBeExecuted[0]->setDescription("check for floating task without priority and cat");

	commandToBeExecuted.push_back(new Command_Add);
	commandToBeExecuted[1]->setDescription("check floating task with priority and cat");
	commandToBeExecuted[1]->setPriority(HIGH);
	commandToBeExecuted[1]->setCategory("test");

	commandToBeExecuted.push_back(new Command_Add);
	commandToBeExecuted[2]->setDescription("check deadline task without priority and cat");
	commandToBeExecuted[2]->setEndDate(endDate);
	commandToBeExecuted[2]->setEndTime(endTime);

	commandToBeExecuted.push_back(new Command_Add);
	commandToBeExecuted[3]->setDescription("check timed task without priority and cat");
	commandToBeExecuted[3]->setStartDate(startDate);
	commandToBeExecuted[3]->setStartTime(startTime);
	commandToBeExecuted[3]->setEndDate(endDate);
	commandToBeExecuted[3]->setEndTime(endTime);

	commandToBeExecuted[0]->execute(_taskList);
	commandToBeExecuted[1]->execute(_taskList);
	commandToBeExecuted[2]->execute(_taskList);
	commandToBeExecuted[3]->execute(_taskList);
	system("pause");
	return 0;
}