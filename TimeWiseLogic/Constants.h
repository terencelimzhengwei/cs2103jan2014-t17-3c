#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#include <string>
#include <ctime>

//@author A0099938B

/******************************************************************************************
//This class is responsible for storing all the constants that would be used across all
//components.
//*****************************************************************************************/


static const int CMD_TYPE_COUNT		    = 13;
static const int LOG_TYPE_COUNT			= 5;
static const int TASK_STATUS_COUNT		= 3;
static const int PREPOSITION_NUM        = 12;
static const int PUNCTUATION_NUM        = 2;
static const int HEADER_COUNT			= 8;
static const int TIME_COUNT             = 2;
static const int FILTER_COUNT           = 4;
static const int SEARCH_COUNT           = 2;
static const int ZERO					= 0;
static const int CLEAR_TYPE_COUNT       = 4;
static const int DISPLAY_TYPE_COUNT     = 5;
const int MAX_HOUR						= 23;
const int MAX_MINUTE					= 59;
const int TIME_DIVISOR					= 100;
const int LOG_TIME_SIZE					= 40;

//Values used in Storage
const int START_VALUE                   = 0;
const int HEADER_DESCRIPTION            = 0;
const int HEADER_START_DATE             = 1;
const int HEADER_END_DATE               = 2;
const int HEADER_START_TIME             = 3;
const int HEADER_END_TIME               = 4;
const int HEADER_CATEGORY               = 5;
const int HEADER_STATUS                 = 6;
const int COLUMN_OUT_OF_BOUND           = 8;
const int REDUCTION_VALUE               = 1;
const int INCREMENT_VALUE				= 1;

enum TASK_STATUS{UNCOMPLETED, OVERDUE, COMPLETED};
enum CMD_TYPE{ADD, DELETE, EDIT, CLEAR, DISPLAY, SEARCH, FILTER, UNDO, REDO, UNDONE, DONE, UNDEFINED};
enum TIMEDATE_STATUS{EARLIER,SAME,LATER};
enum FILTER_TYPE{CATEGORY, DATE};
enum CLEAR_TYPE{ALL,UNCOMPLETED_TASKS,COMPLETED_TASKS,SCREEN};
enum DISPLAY_TYPE{MAIN,SEARCHED,COMPLETE,FILTERED, DONE_DISPLAY};
enum HEADER {DESCRIPTION, START_DATE, START_TIME, DUE_DATE, DUE_TIME, CATEGORY_HEADER, UNDEFINED_HEADER};
enum LOG_TYPE{ INFOLOG, NOTICELOG, WARNINGLOG, ERRORLOG, FATALLOG };
enum FILTER_RESULTS {ALL_TASK_CATEGORY, NO_TASK_CATEGORY,ALL_TASK_DATE, NO_TASK_DATE };
enum SEARCH_RESULTS {ALL_TASK, NO_TASK};

static const std::string LOG_TYPE_STRING[LOG_TYPE_COUNT]         = {"INFOLOG","NOTICELOG","WARNINGLOG","ERRORLOG","FATALLOG"};
static const std::string CMD_TYPE_STRING[CMD_TYPE_COUNT]         = {"add","delete","edit","clear","display", "search", "filter", "undo", "redo",  "undone", "done"};
static const std::string CLEAR_TYPE_STRING[CLEAR_TYPE_COUNT]     = {"all", "main", "completed", ""};
static const std::string DISPLAY_TYPE_STRING[DISPLAY_TYPE_COUNT] = {"main", "", "completed", "", "done"};
static const std::string TASK_STATUS_STRING[TASK_STATUS_COUNT]	 = {"undone","overdue","done"};
static const std::string HEADER_STRING[HEADER_COUNT]             = {"description", "startDate", "startTime","dueDate", "dueTime", "category"};
static const std::string TIME_INDICATOR[TIME_COUNT]              = {"pm", "am"};
static const std::string PREPOSITION[PREPOSITION_NUM]            = {"at", "from", "to", "until", "on", "between", "by", "till", "before", "next", "in", "due"};
static const std::string PUNCTUATION[PUNCTUATION_NUM]            = {",", "."};

const char TASK_SPECIFIER  = '#';
const char DATE_SEPARATOR  = '-';
const char SPACE_DELIMITER = ' ';
const char SLASH_DELIMITER = '/';

const CMD_TYPE DEFAULT_COMMAND_TYPE   = UNDEFINED;
const int DEFAULT_INDEX               = -1;
const TASK_STATUS DEFAULT_TASK_STATUS = UNCOMPLETED;

const int MAX_DATE_NUM_IN_CMD = 2;
const int MAX_TIME_NUM_IN_CMD = 2;

const std::string DEFAULT_EMPTY      = "";
const std::string SPACE_PARAMETER    = " ";
const std::string SLASH_PARAMETER    = "/";
const std::string CATEGORY_SPECIFIER = "#";
const std::string NEW_LINE           = "\n";
const std::string TODAY_DISPLAY      = "Today";
const std::string TMR_DISPLAY        = "Tmrw";

const std::string MARKUP_START       = "<";
const std::string MARKUP_END         = ">";
const std::string MARKUP_ATTRB       = "=";
const std::string MARKUP_MONTH       = "month";
const std::string MARKUP_DATE        = "date";
const std::string MARKUP_DATE_DELIM  = "/";
const std::string MARKUP_TIME_24HR   = "time";
const std::string MARKUP_TIME_AM     = "timeAM";
const std::string MARKUP_TIME_PM     = "timePM";
const std::string MARKUP_TIME_DELIM  = ":";

// These strings store exception messages to be displayed by TiMEWiSE! in the CLI in case of user input errors.
static const char* INVALID_USER_INPUT_DATE_TIME             = "Error! The date or time that you entered has an invalid format.";
static const char* INVALID_USER_INPUT_COMMAND_CLEAR			= "Error! Invalid input for CLEAR command.";
static const char* INVALID_USER_INPUT_FILTER_COMMAND		= "Error! Invalid filtering contents. Please check your date format and hash tag.";
static const char* INVALID_USER_INPUT_EDIT_COMMAND			= "Error! Invalid input for EDIT Command.";
static const char* INVALID_USER_INPUT_DISPLAY_COMMAND		= "Error! Invalid input for DISPLAY command.";
static const char* USER_INPUT_INDEX_OUT_OF_RANGE			= "Error! The task index that you entered is out of range.";
static const char* USER_INPUT_NOT_A_NUMBER					= "Error! The task index that you entered is not a number.";
static const char* MISSING_TASK_DESCRIPTION					= "Error! You have not entered any task description.";
static const char* NO_ARGUMENT_EXCEPTION					= "Error! No input detected.";
static const char* START_DATE_TIME_LATER_THAN_END_DATE_TIME = "Error! Start date/time cannot be later than due date/time.";
static const char* TASK_ALREADY_COMPLETED					= "This task has already been done!";
static const char* TASK_NOT_COMPLETED_YET					= "This task has not been done yet!";

//Feedback strings for successful execution of commands
const std::string ADD_SUCCESS							    = "Task is successfully added.";
const std::string CLASH_EXIST								= "Task is successfully added.\nWARNING: You have tasks that clash!";
const std::string CLEAR_ALL_SUCCESS							= "All tasks are successfully removed.";
const std::string CLEAR_COMPLETED_SUCCESS					= "All completed tasks are successfully removed.";
const std::string CLEAR_UNCOMPLETED_SUCCESS					= "All uncompleted tasks are successfully removed.";
const std::string CLEAR_SEARCHED_SUCCESS					= "All searched tasks are successfully removed." ;
const std::string CLEAR_FILTERED_SUCCESS					= "All filtered tasks are successfully removed." ;
const std::string DELETE_SUCCESS							= "Task is successfully removed.";
const std::string DONE_SUCCESS								= "Task is successfully marked as completed.";
const std::string UNDONE_SUCCESS							= "Task is successfully marked as uncompleted.";
const std::string EDIT_SUCCESS								= "Task is successfully edited.";
const std::string CATEGORY_STRING							= "' category";
const std::string SUCCESS									= "Success!";
const std::string CLOSING_BRACKET							= "'.";
const std::string SEARCH_RESULTS[SEARCH_COUNT]				= {"All tasks displayed contain the keyword '", "No task contains the keyword '" };

const std::string FILTER_CATEGORY_RESULTS[FILTER_COUNT]     = {"All tasks displayed belong to '", "No task belongs to '",
	                                                           "All tasks displayed were scheduled on the same date: ", "No task was scheduled on the date: "} ;

//Feedback strings for  successful execution of undoing the previous command
const std::string UNDO_ADD_SUCCESS							= "Task added is removed!";
const std::string UNDO_DELETE_SUCCESS						= "Task is added back!";
const std::string UNDO_CLEAR_COMPLETED_SUCCESS				= "All completed tasks are added back to the list.";
const std::string UNDO_CLEAR_UNCOMPLETED_SUCCESS			= "All uncompleted tasks are added back to the list.";
const std::string UNDO_CLEAR_ALL_SUCCESS					= "All tasks are added back to the list.";
const std::string UNDO_CLEAR_SEARCHED_SUCCESS				= "All searched tasks are added back to the list.";
const std::string UNDO_CLEAR_FILTERED_SUCCESS				= "All filtered tasks are added back to the list.";
const std::string UNDO_EDIT_SUCCESS							= "Task content is restored to original state!";
const std::string NO_COMMAND_LINE							= "Please key in your command...";
const std::string EXECUTE									= "execute";
const std::string EMPTY_TASKLIST                            = "Unable to undo! You have no more task in your schedule.";

//Strings used for storage
const std::string UNDONE_TASK_TEXTFILE                      = "undoneTasks.txt";
const std::string DONE_TASK_TEXTFILE                        = "doneTasks.txt";
const std::string LOG_MESSAGE_STORAGE                       = "Storage";
const std::string LOG_MESSAGE_SAVING                        = "Saving Tasks to Text file";
const std::string LOG_MESSAGE_RETRIEVAL                     = "Retrieving Tasks from Text file";
const std::string DESCRIPTION_FIELD                         = "Description: ";
const std::string START_DATE_FIELD                          = "Start_Date: ";
const std::string END_DATE_FIELD                            = "End_Date:  ";
const std::string START_TIME_FIELD                          = "Start_Time: ";
const std::string END_TIME_FIELD                            = "End_Time: ";
const std::string CATEGORY_FIELD                            = "Category: ";
const std::string STATUS_FIELD                              = "Status: ";
const std::string SEPARATOR                                 = "==========";

//These are the constants used for dates
const int MONTH_WORD_NUM = 24;
const std::string MONTH_WORD[] = {     
	"January",
	"Jan",
	"February",
	"Feb",
	"March",
	"Mar",
	"April",
	"Apr",
	"May",
	"June",
	"Jun",
	"July",
	"Jul",
	"August",
	"Aug",
	"September",
	"Sept",
	"Sep",
	"October",
	"Oct",
	"November",
	"Nov",
	"December",
	"Dec"
};
const int MONTH_WORD_VALUE[] = {
	1,	//"January",
	1,	//"Jan",
	2,	//"February",
	2,	//"Feb",
	3,	//"March",
	3,	//"Mar",
	4,	//"April",
	4,	//"Apr",
	5,	//"May",
	6,	//"June",
	6,	//"Jun",
	7,	//"July",
	7,	//"Jul",
	8,	//"August",
	8,	//"Aug",
	9,	//"September",
	9,	//"Sept",
	9,	//"Sep",
	10,	//"October",
	10,	//"Oct",
	11,	//"November",
	11,	//"Nov",
	12,	//"December",
	12,	//"Dec"
};

const int DAY_WORD_NUM = 5;
const std::string DAY_WORD[] = {
	"yesterday",
	"ytd",
	"today",
	"tomorrow",
	"tmrw",
	"tmr"
};
const int DAY_WORD_OFFSET[] = {
	-1,	// yesterday
	-1,	// ytd
	 0,	// today
	 1,	// tomorrow
	 1,	// tmr
	 1	// tmrw
};

const int WDAY_WORD_NUM = 24;
const std::string WDAY_WORD[] = {
	"Sundays",
	"Mondays",
	"Tuesdays",
	"Wednesdays",
	"Thursdays",
	"Fridays",
	"Saturdays",
	"Sunday",
	"Sun",
	"Monday",
	"Mon",
	"Tuesday",
	"Tue",
	"Tues",
	"Wednesday",
	"Wed",
	"Thursday",
	"Thur",
	"Thu",
	"Thurs",
	"Friday",
	"Fri",
	"Saturday",
	"Sat",
};
const int WDAY_WORD_VALUE[] = {
	0, // "Sundays",
	1, // "Mondays",
	2, // "Tuesdays",
	3, // "Wednesdays",
	4, // "Thursdays",
	5, // "Fridays",
	6, // "Saturdays"
	0,	// Sunday
	0,	// Sun
	1,	// Monday
	1,	// Mon
	2,	// Tuesday
	2,	// Tue
	2,	// Tues
	3,	// Wednesday
	3,	// Wed
	4,	// Thursday,
	4,	// Thu
	4,	// Thur
	4,	// Thurs
	5,	// Friday
	5,	// Fri
	6,	// Saturday
	6,	// Sat
};

#endif // !_CONSTANTS_H