#include "Command_Edit.h"

//@author A0097277M
Command_Edit::Command_Edit(void){
	_type = EDIT;
	initialiseParameters();
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
	getOriginalTask(tasklist);
	saveOriginalTaskDetails();
	editTaskWithNewParameters();
	createFeedback(EDIT_SUCCESS,feedback);
	tasklist.updateClashStatus();
	tasklist.shiftTask(_editedTask);
	setIndexToBoldInGUI(tasklist);
	return true;
}

void Command_Edit::setDisplayScreen(DISPLAY_TYPE screen){
	_displayScreen = screen;
}

void Command_Edit::setIndex(int index){
	_editIndex = index;
}

bool Command_Edit::undo(TaskList& tasklist, std::string& feedback){
	revertParameters();
	tasklist.updateClashStatus();
	tasklist.shiftTask(_editedTask);
	setIndexToBoldInGUI(tasklist);
	createFeedback(UNDO_EDIT_SUCCESS,feedback);
	return true;
}

bool Command_Edit::noDateAndTime(){
	if(noDate() && noTime()){
		return true;
	}
	return false;
}

bool Command_Edit::noDate(){
	if(noEndDate() && noStartDate()){
		return true;
	}
	return false;
}

bool Command_Edit::noTime(){
	if(noEndTime() && noStartTime()){
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

bool Command_Edit::emptyParameters(){
	if(noDescription() && noCategory() && noDateAndTime()){
		return true;
	}
	return false;
}

bool Command_Edit::noDescription(){
	if(_editedDescription == DEFAULT_EMPTY){
		return true;
	}
	return false;
}

bool Command_Edit::noCategory(){
	if(_editedCategory == DEFAULT_EMPTY){
		return true;
	}
	return false;
}
bool Command_Edit::noEndDate(){
	if(_editedEndDate == NULL){
		return true;
	}
	return false;
}
bool Command_Edit::noStartDate(){
	if(_editedStartDate == NULL){
		return true;
	}
	return false;
}

bool Command_Edit::noStartTime(){
	if(_editedStartTime == NULL){
		return true;
	}
	return false;
}

bool Command_Edit::noEndTime(){
	if(_editedEndTime == NULL){
		return true;
	}
	return false;
}

void Command_Edit::saveOriginalTaskDetails(){
	_originalDescription = _editedTask->getDescription();
	_originalCategory = _editedTask->getTaskCategory();
	_originalEndDate = _editedTask->getEndDate();
	_originalStartDate = _editedTask->getStartDate();
	_originalEndTime = _editedTask->getEndTime();
	_originalStartTime =_editedTask->getStartTime();
}

void Command_Edit::getOriginalTask(TaskList& tasklist){
	switch(_displayScreen){
	case COMPLETE:{
		_editedTask = tasklist.getCompletedTask(_editIndex);
		break;
	}
	case SEARCHED:{
		_editedTask = tasklist.getSearchedTask(_editIndex);
		break;
	}
	case FILTERED:{
		_editedTask = tasklist.getFilteredTask(_editIndex);
		break;
	}
	default:{
		_editedTask = tasklist.getTask(_editIndex);
		break;
	}
	}	
}

void Command_Edit::editTaskWithNewParameters(){
	if(!noDescription()){
		_editedTask->setDescription(_editedDescription);
	}if(!noCategory()){
		_editedTask->setCategory(_editedCategory);
	}if(emptyParameters()){
		resetTimeAndDate();
	}if(!noDateAndTime()){
		if(!noDate()){
			if(!noEndDate()){
				_editedTask->setEndDate(_editedEndDate);
			}if(!noStartDate()){
				_editedTask->setStartDate(_editedStartDate);
			}else{
				_editedTask->setStartDate(NULL);
			}
		}
		if(!noTime()){
			_editedTask->editSchedule(_editedStartTime,_editedEndTime);
		}
	}
}


void Command_Edit::setIndexToBoldInGUI(TaskList& tasklist){
	if(!tasklist.getClashedTask().empty()){
		std::vector<Task*> clashlist = tasklist.getClashedTask();
		for(unsigned int i=0;i<clashlist.size();i++){
			unsigned int index = tasklist.getTaskIndex(clashlist[i]);
			tasklist.addBoldIndex(index);
		}
	}else{
		unsigned int index;
		switch(_displayScreen){
		case MAIN:{
			index = tasklist.getTaskIndex(_editedTask);
			break;
		}
		case SEARCHED:{
			index = tasklist.getTaskIndexInSearchedList(_editedTask);
			break;
		}
		case FILTERED:{
			index = tasklist.getTaskIndexInFilteredList(_editedTask);
			break;
		}
		case COMPLETED:{
			index = tasklist.getTaskIndexInCompletedList(_editedTask);
			break;
		}
		default:
			break;
		}
		tasklist.addBoldIndex(index);
	}
}

void Command_Edit::initialiseParameters(){
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

void Command_Edit::createFeedback(std::string taskFeedback,std::string& feedback){
	feedback=taskFeedback;
}

void Command_Edit::revertParameters(){
	_editedTask->setDescription(_originalDescription);
	_editedTask->setCategory(_originalCategory);
	_editedTask->setEndDate(_originalEndDate);
	_editedTask->setEndTime(_originalEndTime);
	_editedTask->setStartDate(_originalStartDate);
	_editedTask->setStartTime(_originalStartTime);
}
