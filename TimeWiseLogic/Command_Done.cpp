#include "Command_Done.h"


Command_Done::Command_Done(void){
	_type = DONE;
	_currentScreen=NULL;
}


Command_Done::~Command_Done(void){
	_currentScreen=NULL;
}

bool Command_Done::execute(TaskList& tasklist, std::string& feedback){
	if(wasUndone()){
		setTasksAsDone(tasklist);
	}else{
		saveTasks(tasklist);
		setTasksAsDone(tasklist);
	}
	createFeedback(DONE_SUCCESS,feedback);
	lastCmdCalledIs(EXECUTE);
	setIndexToBoldInGUI(tasklist);
	return true;
}

bool Command_Done::undo(TaskList& tasklist, std::string& feedback){

	setDoneTasksAsUndone(tasklist);
    lastCmdCalledIs(CMD_TYPE_STRING[UNDO]);
	createFeedback(UNDONE_SUCCESS,feedback);
	switchScreenTo(_previousScreen);
	setIndexToBoldInGUI(tasklist);
	return true;
}

void Command_Done::setPreviousScreen(DISPLAY_TYPE* screen){
	_currentScreen=screen;
	_previousScreen=*screen;
}

void Command_Done::addDoneIndex(int index){
	_doneTaskIndex.push_back(index);
}

void Command_Done::setIndexToBoldInGUI(TaskList& tasklist){
	unsigned int index;
	switch(*_currentScreen){
	case MAIN:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			index = tasklist.getTaskIndex(_doneTasks[i]);
			tasklist.addLastTaskIndex(index);
		}
		break;
	case SEARCHED:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			index = tasklist.getTaskIndexInSearchedList(_doneTasks[i]);
			tasklist.addLastTaskIndex(index);
		}
		break;
	case FILTERED:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			index = tasklist.getTaskIndexInFilteredList(_doneTasks[i]);
			tasklist.addLastTaskIndex(index);
		}
		break;
	case COMPLETED:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			index = tasklist.getTaskIndexInCompletedList(_doneTasks[i]);
			tasklist.addLastTaskIndex(index);
		}
		break;
	default:
		break;
	}
}

void Command_Done::saveTasks(TaskList& taskList){
	std::vector<Task*>& taskVector=taskList.getUncompletedTaskList();

	switch(*_currentScreen){
	case SEARCHED:
		taskVector = taskList.getSearchResults();
		break;
	case FILTERED:
		taskVector = taskList.getFilterResults();
		break;
	case MAIN:
		break;
	default:
		throw UnableToSetAsDone();
	}
	for(unsigned int i=0;i<_doneTaskIndex.size();i++){
		_doneTasks.push_back(taskVector[_doneTaskIndex[i]]);
		if(_doneTasks[i]->getTaskStatus()==COMPLETED){
			throw UnableToSetAsDone();
		}
	}
}

void Command_Done::setTasksAsDone(TaskList& tasklist){
	switch(*_currentScreen){
	case MAIN:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			int index = tasklist.getTaskIndex(_doneTasks[i]);
			tasklist.setTaskAsDone(index);
		}
		*_currentScreen=COMPLETE;
		break;
	case SEARCHED:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			int index = tasklist.getTaskIndexInSearchedList(_doneTasks[i]);
			tasklist.setSearchedTaskAsDone(index);
		}
		break;
	case FILTERED:
		for(unsigned int i=0;i<_doneTasks.size();i++){
			int index = tasklist.getTaskIndexInFilteredList(_doneTasks[i]);
			tasklist.setFilteredTaskAsDone(index);
		}
		break;
	default:
		throw UnableToSetAsDone();
	}
}

void Command_Done::switchScreenTo(DISPLAY_TYPE screen){
	*_currentScreen = screen;
}

void Command_Done::createFeedback(std::string taskFeedback,std::string& feedback){
	feedback=taskFeedback;
}

void Command_Done::lastCmdCalledIs(std::string cmd){
	_lastCmdCalled=cmd;
}

bool Command_Done::wasUndone(){
	if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
		return true;
	}
	return false;
}

bool Command_Done::wasExecuted(){
	if(_lastCmdCalled==EXECUTE){
		return true;
	}
	return false;
}
void Command_Done::setDoneTasksAsUndone(TaskList& tasklist){
	for(unsigned int i=0;i<_doneTasks.size();i++){
		unsigned int index = tasklist.getTaskIndexInCompletedList(_doneTasks[i]);
		tasklist.setTaskAsUndone(index);
	}
}