#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//For everyone to use, if you have constants to define, define it here

#include <string>
#include <ctime>

static const int CMD_TYPE_COUNT		    = 11;
static const int PRIORITY_COUNT			= 6;
static const int TASK_STATUS_COUNT		= 3;
static const int TASK_TYPE_COUNT		= 3;
static const int MAX_PREPOSITION        = 10;
static const int HEADER_COUNT			= 8;
static const int DAYS_COUNT             = 19;
static const int TIME_COUNT             = 2;



enum TASK_STATUS{UNCOMPLETED, OVERDUE, COMPLETED};
enum TASK_TYPE{TIMED, DEADLINE, FLOATING};
enum CMD_TYPE{ADD, DELETE, EDIT, CLEAR, DISPLAY, BLOCK, SEARCH, FILTER, UNDO, REDO, UNDONE, DONE,ADDEDIT, UNDEFINED};
enum PRIORITY{HIGH,MEDIUM,LOW,DEFAULTPRI};
enum TIMEDATE_STATUS{EARLIER,SAME,LATER};
enum SEARCH_TYPE{KEYWORD,CATEGORY,STATUS,PRI,EMPTYSLOT,DATE,DEFAULT};
enum CLEAR_TYPE{ALL,UNCOMPLETED_TASKS,COMPLETED_TASKS,SCREEN};
enum DISPLAY_TYPE{MAIN,SEARCHED,COMPLETE};
enum HEADER {DESCRIPTION, START_DATE, START_TIME, DUE_DATE, DUE_TIME, CATEGORY_HEADER, PRIORITY_HEADER, UNDEFINED_HEADER};

static const std::string CMD_TYPE_STRING[CMD_TYPE_COUNT] =	
{ "add","delete","edit","clear","display", "done", "undone","undo", "redo","search","filter"};
static const std::string PRIORITY_STRING[PRIORITY_COUNT]		=		{"high","medium","low", "H", "M", "L"};
static const std::string TASK_STATUS_STRING[TASK_STATUS_COUNT]	=		{"undone","overdue","done"};
static const std::string TASK_TYPE_STRING[TASK_TYPE_COUNT]		=		{"timed","deadline","floating"};
static const std::string HEADER_STRING[HEADER_COUNT] = {"description", "startDate", "startTime","dueDate", "dueTime", "category", "priority"};
static const std::string DAYS_IN_WEEK[DAYS_COUNT] = 
{"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", 
"mon", "tues", "wed", "thurs", "fri", "sat", "sun", "today", "tomorrow", "2day", "tmr", "tml"};
static const std::string TIME_INDICATOR[TIME_COUNT] = {"pm", "am"};

const char TASK_SPECIFIER = '#';
const char DATE_SEPARATOR = '-';

const std::string PREPOSITION[MAX_PREPOSITION] = {"at", "from", "to", "until", "on", "between", "by", "till", "before", "next"};

const CMD_TYPE DEFAULT_COMMAND_TYPE = UNDEFINED;
const int DEFAULT_INDEX = -1;
const PRIORITY DEFAULT_PRIORITY = LOW;
const TASK_TYPE DEFAULT_TASK_TYPE = FLOATING;
const TASK_STATUS DEFAULT_TASK_STATUS = UNCOMPLETED;
const std::string DEFAULT_EMPTY = "";

// These string store exception messages to be displayed by TiMEWiSE! in the CLI 
// in case of user input error.

static const char* USER_INPUT_INDEX_OUT_OF_RANGE_EXCEPTION = "Error! The task index that you entered is out of range.";
static const char* MISSING_TASK_DESCRIPTION = "Error! You have not entered any task description";
static const char* INVALID_USER_INPUT_COMMAND_WORD = "Error! Invalid command!";
static const char* NO_ARGUMENT_EXCEPTION = "Error! No input detected";
static const char* USER_INPUT_NOT_A_NUMBER = "Error! The task index that you entered is not a number";
static const char* INVALID_USER_INPUT_HEADER = "Error! The header that you enter is invalid";
static const char* TASKLIST_EMPTY = "You have no tasks scheduled at this moment!";
static const char* INVALID_USER_INPUT_DATE_TIME = "Error! The date or time that you entered has an invalid format";
static const char* INVALID_USER_INPUT_COMMAND_CLEAR = "Error! Invalid parameters for Clear. Only accepts ALL,DONE,UNDONE";
static const char* TASK_ALREADY_COMPLETED = "This task has already been done";
#endif // !_CONSTANTS_H
