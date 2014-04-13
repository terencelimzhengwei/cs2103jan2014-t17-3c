

//Exceptions. If any of you have error messages please comment the error here. Terence
//will convert them into exceptions.
//this class is responsible for giving feedback to user with regard to command format only
//will prompt users of the wrong format that they have keyed in.
#pragma once 
#ifndef EXCEPTIONS_H 
#define EXCEPTIONS_H
#include <exception> 
#include "Constants.h"
// This class throws a out of range exception when the index input is 
// lesser than 0 or more than the number of tasks in the task list.
class OutOfRangeException : public std::exception {
public:
	virtual const char* what() const throw(); 
};
/* This class throws an invalid input filename exception when the argument has an 
// invalid file extension name. 
class InvalidUserInputFilenameException : public std::exception {
public: virtual const char* what() const throw(); 
};*/
// This class throws a no argument exception when the argument input by user is 
// empty. 
class NoArgumentException : public std::exception {
public: 
	virtual const char* what() const throw(); 
};
// This class throws an invalid  delete format exception when the string input 
// by the user to delete/mark a task does not contain a number.
class NotANumberException : public std::exception {
public: 
	virtual const char* what() const throw(); 
};
 //This class throws an invalid user input command exception when the command word input by the 
// user is not a command recognised by TiMEWiSE!.
class InvalidCommandWordException : public std::exception { 
public: 
	virtual const char* what() const throw(); 
};
// This class throws an invalid user input add command when no description was added.
class InvalidAddCommandInputException: public std::exception {
public:
	virtual const char* what() const throw();
};
//For edit command, when the user enters headers which TiMEWiSE! does not support
class EmptyTaskListException: public std::exception {
public:
	virtual const char* what() const throw();
};
class InvalidDateTimeFormatException: public std::exception {
public:
	virtual const char* what() const throw();
};
class InvalidClearCommandInputException: public std::exception {
public:
	virtual const char* what() const throw();
};
class UnableTosetAsDone: public std:: exception {
public:
	virtual const char* what() const throw();
};

class UnableToUndoneUncompletedTasks: public std:: exception {
public:
	virtual const char* what() const throw();
};

class CorruptedFile: public std:: exception {
};

// this exception is thrown when the users enter:
//1. A start date that is later than a due date
//2. A start time that is later than a due time (on the same day)
class InvalidStartEndDateTime: public std::exception {
public:
	virtual const char* what() const throw();
};
class InvalidFilterParameters: public std::exception {
public:
	virtual const char* what() const throw();
};
class InvalidEditIndexMissing: public std::exception {
public:
	virtual const char* what() const throw();
};
class InvalidDisplayCommandException: public std::exception {
public:
	virtual const char* what() const throw();
};
#endif