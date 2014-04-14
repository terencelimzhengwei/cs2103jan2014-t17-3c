//@author A0097277M
#include "Command_Add.h"

Command_Add::Command_Add() {
	initDefaultValues();
}
Command_Add::~Command_Add(void) {
	resetDateAndTime();
}

//Setter functions for setting of attributes in the task
void Command_Add::setDescription(std::string description){
	_taskDescription = description;
}
void Command_Add::setCategory(std::string category) {
	_category = category;
}
void Command_Add::setStartDate(Date& date) {
	_startDate = new Date(date);
}
void Command_Add::setStartTime(ClockTime& startTime) {
	_startTime = new ClockTime(startTime);
}
void Command_Add::setEndTime(ClockTime& endTime) {
	_endTime = new ClockTime(endTime);
}
void Command_Add::setEndDate(Date& date){
	_endDate = new Date(date);
}
void Command_Add::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen = *screen;
	_currentScreen = screen;
}
bool Command_Add::execute(TaskList& tasklist,std::string& feedback){
	switchScreenTo(MAIN);
	if(wasUndone()){
		redo(tasklist);
	} else {
		createTask(tasklist);
	}
	createFeedback(tasklist,feedback);
	lastCmdCalledIs(EXECUTE);
	setIndexToBoldInGUI(tasklist);
	return true;
}
bool Command_Add::undo(TaskList& taskList, std::string& feedback){
	if (taskList.isEmpty()){
		createFeedback(EMPTY_TASKLIST,feedback);
		return false;
	} else {
		removeAddedTask(taskList);
		createFeedback(UNDO_ADD_SUCCESS,feedback);
		switchScreenTo(_previousScreen);
		lastCmdCalledIs(CMD_TYPE_STRING[UNDO]);
		return true;
	}
}

void Command_Add::initDefaultValues(){
	_type = ADD;	
	_taskDescription = DEFAULT_EMPTY;
	_category = DEFAULT_EMPTY;
	_endDate = NULL;
	_endTime = NULL;
	_startDate = NULL;
	_startTime = NULL;
	_addedTask = NULL;
	_currentScreen = NULL;
}

void Command_Add::resetDateAndTime(){
	resetStartTime();
	resetStartDate();
	resetEndDate();
	resetEndTime();
	resetTask();
}

bool Command_Add::hasStartTime(){
	return _startTime!=NULL;
}

bool Command_Add::hasEndTime(){
	return _endTime!=NULL;
}

bool Command_Add::hasEndDate(){
	return _endDate!=NULL;
}

bool Command_Add::hasStartDate(){
	return _startDate!=NULL;
}

void Command_Add::resetStartTime(){
	if(hasStartTime()){
		_startTime = NULL;
	}
}

void Command_Add::resetEndTime(){
	if(hasEndTime()){
		_endTime = NULL;
	}
}

void Command_Add::resetStartDate(){
	if(hasStartDate()){
		_startDate = NULL;
	}
}

void Command_Add::resetEndDate(){
	if(hasEndDate()){
		_endDate = NULL;
	}
}

void Command_Add::resetTask(){
	_addedTask=NULL;
}

void Command_Add::redo(TaskList& tasklist){
	tasklist.addTask(*_addedTask);
	setIndexToBoldInGUI(tasklist);
}

bool Command_Add::wasUndone(){
	if(_lastCmdCalled==CMD_TYPE_STRING[UNDO]){
		return true;
	}
	return false;
}

bool Command_Add::wasExecuted(){
	if(_lastCmdCalled==EXECUTE){
		return true;
	}
	return false;
}

void Command_Add::createTask(TaskList& tasklist){
	_addedTask = new Task;
	_addedTask->setDescription(_taskDescription);
	_addedTask->setCategory(_category);
	_addedTask->setSchedule(_startDate,_endDate,_startTime,_endTime);
	tasklist.addTask(*_addedTask);
}

bool Command_Add::isClash(TaskList& tasklist){
	if(!tasklist.getClashedTask().empty()){
		return true;
	}
	return false;
}

void Command_Add::createFeedback(TaskList& tasklist,std::string& feedback){
	if(isClash(tasklist)){
		createFeedback(CLASH_EXIST, feedback);
	}else{
		createFeedback(ADD_SUCCESS, feedback);
	}
}

void Command_Add::createFeedback(std::string taskFeedback,std::string& feedback){
	feedback=taskFeedback;
}

void Command_Add::switchScreenTo(DISPLAY_TYPE screen){
	*_currentScreen = screen;
}

void Command_Add::lastCmdCalledIs(std::string cmd){
	_lastCmdCalled=cmd;
}

void Command_Add::setIndexToBoldInGUI(TaskList& tasklist){
	if(!tasklist.getClashedTask().empty()){
		std::vector<Task*> clashlist = tasklist.getClashedTask();
		for(unsigned int i=0;i<clashlist.size();i++){
			unsigned int index = tasklist.getTaskIndex(clashlist[i]);
			tasklist.addBoldIndex(index);
		}
	}else{
		unsigned int index = tasklist.getTaskIndex(_addedTask);
		tasklist.addBoldIndex(index);
	}
}

void Command_Add::removeAddedTask(TaskList& tasklist){
	unsigned int index = tasklist.getTaskIndex(_addedTask);
	tasklist.deleteTaskFromUncompletedList(index);
}


