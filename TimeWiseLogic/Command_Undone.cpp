#include "Command_Undone.h"


Command_Undone::Command_Undone(void){
	_type = UNDONE;
}


Command_Undone::~Command_Undone(void){
	_undoneTaskIndex.clear();
	_undoneTasks.clear();
}

bool Command_Undone::execute(TaskList& tasklist, std::string& feedback){
	if(_displayType == COMPLETE){
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_undoneTasks.size();i++){
				unsigned int index = tasklist.getTaskIndexInCompletedList(_undoneTasks[i]);
				tasklist.setTaskAsUndone(index);
			}
			_lastCmdCalled=EXECUTE;
			feedback = UNDONE_SUCCESS;
			return true;
		}
		for(unsigned int i=0;i<_undoneTaskIndex.size();i++){
			_undoneTasks.push_back(tasklist.setTaskAsUndone(_undoneTaskIndex[i]));
		}
		_lastCmdCalled=EXECUTE;
		feedback = UNDONE_SUCCESS;
		return true;
	}else{
		throw UnableToUndoneUncompletedTasks();
		return false;
	}
}

bool Command_Undone::undo(TaskList& tasklist, std::string& feedback){
	for(unsigned int i=0;i<_undoneTasks.size();i++){
		int index = tasklist.getTaskIndex(_undoneTasks[i]);
		tasklist.setTaskAsDone(index);
	}
	_lastCmdCalled=CMD_TYPE_STRING[UNDO];
	feedback = DONE_SUCCESS;
	return true;
}

void Command_Undone::setDisplayScreen(DISPLAY_TYPE screen){
	_displayType = screen;
}

void Command_Undone::addUndoneIndex(int index){
	_undoneTaskIndex.push_back(index);
}
