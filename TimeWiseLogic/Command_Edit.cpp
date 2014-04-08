#include "Command_Edit.h"


Command_Edit::Command_Edit(void){
	_type = EDIT;
	_editedDescription = DEFAULT_EMPTY;
	_editedCategory = DEFAULT_EMPTY;
	_editedEndDate = NULL;
	_editedStartDate = NULL;
	_editedEndTime = NULL;
	_editedStartTime = NULL;

	_originalDescription = DEFAULT_EMPTY;
	_originalCategory = DEFAULT_EMPTY;
	_originalEndDate = NULL;
	_originalStartDate = NULL;
	_originalEndTime = NULL;
	_originalStartTime = NULL;

	_editedTask = NULL;
}


Command_Edit::~Command_Edit(void){
}

void Command_Edit::setDescription(std::string description){
	_editedDescription = description;
}

void Command_Edit::setCategory(std::string category){
	_editedCategory = category;
}

void Command_Edit::setEndDate(Date* endDate){
	_editedEndDate = endDate;
}

void Command_Edit::setStartDate(Date* startDate){
	_editedStartDate = startDate;
}

void Command_Edit::setStartTime(ClockTime* startTime){
	_editedStartTime = startTime;
}

void Command_Edit::setEndTime(ClockTime* endTime){
	_editedEndTime = endTime;
}

bool Command_Edit::execute(TaskList& tasklist, std::string& feedback){
	switch(_displayScreen){
	case MAIN:
		_editedTask = tasklist.getTask(_editIndex);
		break;
	case COMPLETE:
		_editedTask = tasklist.getCompletedTask(_editIndex);
		break;
	case SEARCHED:
		_editedTask = tasklist.getSearchedTask(_editIndex);
		break;
	case FILTERED:
		_editedTask = tasklist.getFilteredTask(_editIndex);
		break;
	default:
		return false;
	}	

	_originalDescription = _editedTask->getDescription();
	_originalCategory = _editedTask->getTaskCategory();
	_originalEndDate = _editedTask->getEndDate();
	_originalStartDate = _editedTask->getStartDate();
	_originalEndTime = _editedTask->getEndTime();
	_originalStartTime =_editedTask->getStartTime();
	if(_editedDescription != DEFAULT_EMPTY){
		_editedTask->setDescription(_editedDescription);
	}else if(_editedCategory != DEFAULT_EMPTY){
		_editedTask->setCategory(_editedCategory);
	}else{
		if(noDateAndTime()){
			resetTimeAndDate();
		}
	}
	if(!noDateAndTime()){
		if(!noDate()){
			if(_editedEndDate != NULL){
				_editedTask->setEndDate(_editedEndDate);
			}if(_editedStartDate != NULL){
				_editedTask->setStartDate(_editedStartDate);
			}else{
				_editedTask->setStartDate(NULL);
			}
		}
		if(!noTime()){
			_editedTask->editSchedule(_editedStartTime,_editedEndTime);
		}
	}
	feedback = EDIT_SUCCESS;
	tasklist.updateClashStatus();
	tasklist.shiftTask(_editedTask);
	tasklist.setLastTaskIndex(tasklist.getTaskIndex(_editedTask));
	return true;
}

void Command_Edit::setDisplayScreen(DISPLAY_TYPE screen){
	_displayScreen = screen;
}

void Command_Edit::setIndex(int index){
	_editIndex = index;
}

bool Command_Edit::undo(TaskList& tasklist, std::string& feedback){
	_editedTask->setDescription(_originalDescription);
	_editedTask->setCategory(_originalCategory);
	_editedTask->setEndDate(_originalEndDate);
	_editedTask->setEndTime(_originalEndTime);
	_editedTask->setStartDate(_originalStartDate);
	_editedTask->setStartTime(_originalStartTime);
	tasklist.updateClashStatus();
	tasklist.shiftTask(_editedTask);
	feedback = UNDO_EDIT_SUCCESS;
	return true;
}

bool Command_Edit::noDateAndTime(){
	if(_editedEndDate == NULL  && _editedEndTime ==  NULL && _editedStartDate == NULL &&_editedStartTime == NULL){
		return true;
	}
	return false;
}

bool Command_Edit::noDate(){
	if(_editedEndDate == NULL && _editedStartDate == NULL){
		return true;
	}
	return false;
}

bool Command_Edit::noTime(){
	if(_editedEndTime == NULL && _editedStartTime == NULL){
		return true;
	}
	return false;
}

void Command_Edit::resetTimeAndDate(){
	_editedTask->setEndDate(NULL);
	_editedTask->setEndTime(NULL);
	_editedTask->setStartTime(NULL);
	_editedTask->setStartDate(NULL);
}
