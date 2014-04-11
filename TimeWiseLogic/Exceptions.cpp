#include "Exceptions.h"

// This file stores the various exception classes that are required for TextBuddy.
const char* InvalidCommandWordException::what() const throw(){
	return INVALID_USER_INPUT_COMMAND_WORD; 
}
const char* OutOfRangeException::what() const throw(){
	return USER_INPUT_INDEX_OUT_OF_RANGE_EXCEPTION; 
}
const char* InvalidAddCommandInputException::what() const throw(){
	return MISSING_TASK_DESCRIPTION; 
}

const char* NoArgumentException::what() const throw(){ 
	return NO_ARGUMENT_EXCEPTION; 
}

const char* NotANumberException::what() const throw(){
	return USER_INPUT_NOT_A_NUMBER; 
}

const char* EmptyTaskListException::what() const throw(){ 
	return TASKLIST_EMPTY; 
}

const char* InvalidDateTimeFormatException::what() const throw(){
	return INVALID_USER_INPUT_DATE_TIME;
}

const char* InvalidClearCommandInputException::what() const throw(){
	return INVALID_USER_INPUT_COMMAND_CLEAR;
}
const char* UnableTosetAsDone::what() const throw() {
	return TASK_ALREADY_COMPLETED;
}

const char* UnableToUndoneUncompletedTasks::what() const throw() {
	return TASK_NOT_COMPLETED_YET;
}

const char* InvalidStartEndDateTime::what() const throw() {
	return START_DATE_TIME_LATER_THAN_END_DATE_TIME;
}
const char* InvalidFilterParameters::what() const throw() {
	return INVALID_FILTER_INPUT;
}