#include "TimeWiseLogic.h"
#include <iostream>

int main(){
	TimeWiseLogic _logic;
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
	}
	system("pause");
	return 0;
}