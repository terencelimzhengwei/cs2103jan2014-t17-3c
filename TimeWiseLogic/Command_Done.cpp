#include "Command_Done.h"


Command_Done::Command_Done(void){
	_type = DONE;
	_currentScreen=NULL;
}


Command_Done::~Command_Done(void){
	_currentScreen=NULL;
}

bool Command_Done::execute(TaskList& tasklist, std::string& feedback){
	switch(_previousScreen){
	case MAIN:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_doneTaskIndex.size();i++){
				tasklist.setTaskAsDone(_doneTaskIndex[i]);
			}
		}else{
			for(unsigned int i=0;i<_doneTaskIndex.size();i++){
				_doneTasks.push_back(tasklist.setTaskAsDone(_doneTaskIndex[i]));
			}
		}
		feedback = DONE_SUCCESS;
		_lastCmdCalled = EXECUTE;
		*_currentScreen=COMPLETE;
		setIndexToBoldInGUI(tasklist);
		return true;
	case SEARCHED:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_doneTaskIndex.size();i++){
				tasklist.setSearchedTaskAsDone(_doneTaskIndex[i]);
			}
		}else{
			for(unsigned int i=0;i<_doneTaskIndex.size();i++){
				_doneTasks.push_back(tasklist.setSearchedTaskAsDone(_doneTaskIndex[i]));
			}
		}
		feedback = DONE_SUCCESS;
		_lastCmdCalled = EXECUTE;
		*_currentScreen=COMPLETE;
		setIndexToBoldInGUI(tasklist);
		return true;
	case FILTERED:
		if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
			for(unsigned int i=0;i<_doneTaskIndex.size();i++){
				tasklist.setFilteredTaskAsDone(_doneTaskIndex[i]);
			}
		}else{
			for(unsigned int i=0;i<_doneTaskIndex.size();i++){
				_doneTasks.push_back(tasklist.setFilteredTaskAsDone(_doneTaskIndex[i]));
			}
		}
		feedback = DONE_SUCCESS;
		_lastCmdCalled = EXECUTE;
		*_currentScreen=COMPLETE;
		setIndexToBoldInGUI(tasklist);
		return true;
	default:
		throw UnableTosetAsDone();
		return false;
	}
}

bool Command_Done::undo(TaskList& tasklist, std::string& feedback){

	for(unsigned int i=0;i<_doneTasks.size();i++){
		unsigned int index = tasklist.getTaskIndexInCompletedList(_doneTasks[i]);
		tasklist.setTaskAsUndone(index);
		if(_previousScreen == SEARCHED){
			tasklist.addTaskToSearchedList(*_doneTasks[i]);
		}else if(_previousScreen == FILTERED){
			tasklist.addTaskToFilteredList(*_doneTasks[i]);
		}
	}
    _lastCmdCalled = CMD_TYPE_STRING[UNDO];
	feedback = UNDONE_SUCCESS;
	*_currentScreen=_previousScreen;
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