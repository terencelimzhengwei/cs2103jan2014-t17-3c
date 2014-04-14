#include "Exceptions.h"
//@Tran Hue Mai A0099938B

// This file stores the various exception classes that are required for TimeWise.

const char* OutOfRangeException::what() const throw(){
	return USER_INPUT_INDEX_OUT_OF_RANGE; 
}

const char* NoArgumentException::what() const throw(){ 
	return NO_ARGUMENT_EXCEPTION; 
}

const char* NotANumberException::what() const throw(){
	return USER_INPUT_NOT_A_NUMBER; 
}

const char* UnableToSetAsDone::what() const throw() {
	return TASK_ALREADY_COMPLETED;
}

const char* UnableToUndoneUncompletedTasks::what() const throw() {
	return TASK_NOT_COMPLETED_YET;
}

const char* InvalidAddCommandInputException::what() const throw(){
	return MISSING_TASK_DESCRIPTION; 
}

const char* InvalidStartEndDateTime::what() const throw() {
	return START_DATE_TIME_LATER_THAN_END_DATE_TIME;
}

const char* InvalidFilterCommandInputException::what() const throw() {
	return INVALID_USER_INPUT_FILTER_COMMAND;
}

const char* InvalidEditCommandInputException::what() const throw() {
	return INVALID_USER_INPUT_EDIT_COMMAND;
}

const char* InvalidDisplayCommandException::what() const throw() {
	return INVALID_USER_INPUT_DISPLAY_COMMAND;
}

const char* InvalidDateTimeFormatException::what() const throw(){
	return INVALID_USER_INPUT_DATE_TIME;
}

const char* InvalidClearCommandInputException::what() const throw(){
	return INVALID_USER_INPUT_COMMAND_CLEAR;
}