#include "Command_Undone.h"

//@author A0097277M
Command_Undone::Command_Undone(void){
	_type = UNDONE;
}

Command_Undone::~Command_Undone(void){
	_undoneTaskIndex.clear();
	_undoneTasks.clear();
}

bool Command_Undone::execute(TaskList& tasklist, std::string& feedback){
	if(wasUndone()){
		setTasksAsUndone(tasklist);
	}else{
		saveTasks(tasklist);
		setTasksAsUndone(tasklist);
	}
	lastCmdCalledIs(EXECUTE);
	createFeedback(UNDONE_SUCCESS,feedback);
	setIndexToBoldInGUI(tasklist);
	return true;
}

bool Command_Undone::undo(TaskList& tasklist, std::string& feedback){
	for(unsigned int i=0;i<_undoneTasks.size();i++){
		int index = tasklist.getTaskIndex(_undoneTasks[i]);
		tasklist.setTaskAsDone(index);
	}
	lastCmdCalledIs(CMD_TYPE_STRING[UNDO]);
	createFeedback(DONE_SUCCESS,feedback);
	switchScreenTo(_previousScreen);
	setIndexToBoldInGUI(tasklist);
	return true;
}

void Command_Undone::setPreviousScreen(DISPLAY_TYPE* screen){
	_currentScreen=screen;
	_previousScreen=*screen;
}

void Command_Undone::addUndoneIndex(int index){
	_undoneTaskIndex.push_back(index);
}

void Command_Undone::setIndexToBoldInGUI(TaskList& tasklist){
	unsigned int index;
	switch(*_currentScreen){
	case MAIN:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			index = tasklist.getTaskIndex(_undoneTasks[i]);
			tasklist.addBoldIndex(index);
		}
		break;
	}
	case SEARCHED:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			index = tasklist.getTaskIndexInSearchedList(_undoneTasks[i]);
			tasklist.addBoldIndex(index);
		}
		break;
	}
	case FILTERED:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			index = tasklist.getTaskIndexInFilteredList(_undoneTasks[i]);
			tasklist.addBoldIndex(index);
		}
		break;
	}
	case COMPLETED:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			index = tasklist.getTaskIndexInCompletedList(_undoneTasks[i]);
			tasklist.addBoldIndex(index);
		}
		break;
	}
	default:
		break;
	}
}

void Command_Undone::saveTasks(TaskList& taskList){
	std::vector<Task*>& taskVector=taskList.getCompletedTaskList();
	switch(*_currentScreen){
	case SEARCHED:{
		taskVector = taskList.getSearchResults();
		break;
	}
	case FILTERED:{
		taskVector = taskList.getFilterResults();
		break;
	}
	case COMPLETE:{
		break;
	}
	default:
		throw UnableToUndoneUncompletedTasks();
	}

	for(unsigned int i=0;i<_undoneTaskIndex.size();i++){
		_undoneTasks.push_back(taskVector[_undoneTaskIndex[i]]);
		if(_undoneTasks[i]->getTaskStatus()==UNCOMPLETED){
			throw UnableToUndoneUncompletedTasks();
		}
	}
}

void Command_Undone::setTasksAsUndone(TaskList& tasklist){
	switch(*_currentScreen){
	case COMPLETE:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			int index = tasklist.getTaskIndexInCompletedList(_undoneTasks[i]);
			tasklist.setTaskAsUndone(index);
		}
		*_currentScreen=MAIN;
		break;
	}
	case SEARCHED:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			int index = tasklist.getTaskIndexInSearchedList(_undoneTasks[i]);
			tasklist.setSearchedTaskAsUndone(index);
		}
		break;
	}
	case FILTERED:{
		for(unsigned int i=0;i<_undoneTasks.size();i++){
			int index = tasklist.getTaskIndexInFilteredList(_undoneTasks[i]);
			tasklist.setFilteredTaskAsUndone(index);
		}
		break;
	}
	default:
		throw UnableToUndoneUncompletedTasks();
	}
}

void Command_Undone::switchScreenTo(DISPLAY_TYPE screen){
	*_currentScreen = screen;
}

void Command_Undone::createFeedback(std::string taskFeedback,std::string& feedback){
	feedback=taskFeedback;
}

void Command_Undone::lastCmdCalledIs(std::string cmd){
	_lastCmdCalled=cmd;
}

bool Command_Undone::wasUndone(){
	if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
		return true;
	}
	return false;
}

bool Command_Undone::wasExecuted(){
	if(_lastCmdCalled==EXECUTE){
		return true;
	}
	return false;
}
