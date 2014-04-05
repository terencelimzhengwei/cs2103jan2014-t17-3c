#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//For everyone to use, if you have constants to define, define it here

#include <string>
#include <ctime>

static const int CMD_TYPE_COUNT		    = 13;
static const int PRIORITY_COUNT			= 6;
static const int TASK_STATUS_COUNT		= 3;
static const int TASK_TYPE_COUNT		= 3;
static const int MAX_PREPOSITION        = 12;
static const int HEADER_COUNT			= 8;
static const int DAYS_COUNT             = 19;
static const int TIME_COUNT             = 2;
static const int FILTER_COUNT           = 4;
static const int SEARCH_COUNT           = 2;



enum TASK_STATUS{UNCOMPLETED, OVERDUE, COMPLETED};
enum TASK_TYPE{TIMED, DEADLINE, FLOATING};
enum CMD_TYPE{ADD, DELETE, EDIT, CLEAR, DISPLAY, BLOCK, SEARCH, FILTER, UNDO, REDO, UNDONE, DONE, UNDEFINED};
enum PRIORITY{HIGH,MEDIUM,LOW,DEFAULTPRI};
enum TIMEDATE_STATUS{EARLIER,SAME,LATER};
enum FILTER_TYPE{CATEGORY,PRI,DATE};
enum CLEAR_TYPE{ALL,UNCOMPLETED_TASKS,COMPLETED_TASKS,SCREEN};
enum DISPLAY_TYPE{MAIN,SEARCHED,COMPLETE,FILTERED};
enum HEADER {DESCRIPTION, START_DATE, START_TIME, DUE_DATE, DUE_TIME, CATEGORY_HEADER, PRIORITY_HEADER, UNDEFINED_HEADER};

static const std::string CMD_TYPE_STRING[CMD_TYPE_COUNT] =	
{ "add","delete","edit","clear","display","block", "search", "filter", "undo", "redo",  "undone", "done"};
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

const std::string PREPOSITION[MAX_PREPOSITION] = {"at", "from", "to", "until", "on", "between", "by", "till", "before", "next", "in", "due"};

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
static const char* USER_INPUT_NOT_A_NUMBER = "Error! The task index that you entered is not a number.";
static const char* INVALID_USER_INPUT_HEADER = "Error! The header that you enter is invalid";
static const char* TASKLIST_EMPTY = "You have no tasks scheduled at this moment!";
static const char* INVALID_USER_INPUT_DATE_TIME = "Error! The date or time that you entered has an invalid format";
static const char* INVALID_USER_INPUT_COMMAND_CLEAR = "Error! Invalid parameters for Clear. Only accepts ALL,DONE,UNDONE";
static const char* TASK_ALREADY_COMPLETED = "This task has already been done!";
static const char* UNABLE_TO_EDIT_COMPLETED_TASKS = "This task has been completed. Please type 'undone' in order to edit it";
static const char* TASK_NOT_COMPLETED_YET = "This task has not been done yet!";
static const char* START_DATE_TIME_LATER_THAN_END_DATE_TIME = "Error! Start date/time cannot be later than due date/time.";
//Feedback strings
 
const std::string ADD_SUCCESS = " Task is successfully added";
const std::string CLEAR_ALL_SUCCESS = "All tasks are successfully removed.";
const std::string CLEAR_COMPLETED_SUCCESS = "All completed tasks are successfully removed.";
const std::string CLEAR_UNCOMPLETED_SUCCESS = "All uncompleted tasks are successfully removed.";
const std::string CLEAR_SEARCHED_SUCCESS = "All searched tasks are successfully removed." ;
const std::string CLEAR_FILTERED_SUCCESS = "All filtered tasks are successfully removed." ;
const std::string DELETE_SUCCESS = "Task is successfully removed.";
const std::string DONE_SUCCESS = "Task is successfully marked as completed.";
const std::string UNDONE_SUCCESS = "Task is successfully marked as uncompleted.";
const std::string EDIT_SUCCESS = "Task is successfully edited.";
const std::string CATEGORY_STRING = "' category";
const std::string FILTER_CATEGORY_RESULTS[FILTER_COUNT] = {"All tasks displayed belong to '", "No task belongs to '",
	                                                       "All tasks displayed were scheduled on the same date: ", "No task was scheduled on the date: "} ;
const std::string SUCCESS = "Success!";
const std::string SEARCH_RESULTS[SEARCH_COUNT] = {"All tasks displayed contain the keyword '",
												"No task contains the keyword '" };
const std::string EMPTY_TASKLIST = "Cannot undo! your task list is empty!";
const std::string CLOSING_BRACKET = "'.";
//feedback for undo
const std::string UNDO_ADD_SUCCESS = "Task added is removed!";
const std::string UNDO_DELETE_SUCCESS = "Task is added back!";
const std::string UNDO_CLEAR_COMPLETED_SUCCESS = "All completed tasks are added back to the list.";
const std::string UNDO_CLEAR_UNCOMPLETED_SUCCESS = "All uncompleted tasks are added back to the list.";
const std::string UNDO_CLEAR_ALL_SUCCESS = "All tasks are added back to the list.";
const std::string UNDO_CLEAR_SEARCHED_SUCCESS = "All searched tasks are added back to the list.";
const std::string UNDO_CLEAR_FILTERED_SUCCESS = "All filtered tasks are added back to the list.";
const std::string UNDO_EDIT_SUCCESS = "Task content is restored to original state!";
const std::string NO_COMMAND_LINE = "Please key in your command...";
const std::string EXECUTE = "execute";
#endif // !_CONSTANTS_H
