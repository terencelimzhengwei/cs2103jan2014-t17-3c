//@author A0099938B
#pragma once 
#ifndef EXCEPTIONS_H 
#define EXCEPTIONS_H
#include <exception> 
#include "Constants.h"

/******************************************************************************************
//This class is responsible for giving feedback to user with regard to command format only
// will prompt users of the wrong format that they have keyed in.
//*****************************************************************************************/


// This class throws an error message when the index input is 
// lesser than 0 or more than the number of tasks in the task list.
class OutOfRangeException : public std::exception {
public:
	virtual const char* what() const throw(); 
};

// This class throws an error message when the argument input by user is  empty. 
class NoArgumentException : public std::exception {
public: 
	virtual const char* what() const throw(); 
};
// This class throws an error message when the string input 
// by the user to delete/mark a task does not contain a number.
class NotANumberException : public std::exception {
public: 
	virtual const char* what() const throw(); 
};
// This class throws an error message when the user tries to mark a completed task as completed
class UnableToSetAsDone: public std:: exception {
public:
	virtual const char* what() const throw();
};
// This class throws an error message when the user tries to mark an uncompleted task as uncompleted
class UnableToUndoneUncompletedTasks: public std:: exception {
public:
	virtual const char* what() const throw();
};

class CorruptedFile: public std:: exception {
};

 
// This class throws an error message when no description was added.
class InvalidAddCommandInputException: public std::exception {
public:
	virtual const char* what() const throw();
};
// This class throws an error message when there are more than 2 dates/ times keyed in by users
class InvalidDateTimeFormatException: public std::exception {
public:
	virtual const char* what() const throw();
};
// This class throws an error message when the users keys in an invalid clear parameter
// Accepted command formats are: clear done, clear undone, clear all and clear
class InvalidClearCommandInputException: public std::exception {
public:
	virtual const char* what() const throw();
};

// this exception is thrown when the users enter:
//1. A start date that is later than a due date
//2. A start time that is later than a due time (on the same day)
class InvalidStartEndDateTime: public std::exception {
public:
	virtual const char* what() const throw();
};

// this exception is thrown when the users enter:
//1. An invalid date format
//2. No hash tag to indicate the category
class InvalidFilterCommandInputException: public std::exception {
public:
	virtual const char* what() const throw();
};

//this exception is thrown when the users enter:
//1. an invalid index format (not a number)
//2. new content without an index
class InvalidEditCommandInputException: public std::exception {
public:
	virtual const char* what() const throw();
};
// this exception is thrown when the users enter an invalid display parameter
// Accepted command formats are: display main, display completed and display done.
class InvalidDisplayCommandException: public std::exception {
public:
	virtual const char* what() const throw();
};
#endif