#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//For everyone to use, if you have constants to define, define it here

#include <string>
#include <ctime>

static const int CMD_TYPE_COUNT		    = 8;
static const int PRIORITY_COUNT			= 3;
static const int TASK_STATUS_COUNT		= 3;
static const int TASK_TYPE_COUNT		= 3;
static const int MAX_PREPOSITION        = 9;


enum TASK_STATUS{UNCOMPLETED,OVERDUE,COMPLETED};
enum TASK_TYPE{TIMED,DEADLINE,FLOATING};
enum CMD_TYPE{ADD,DELETE,EDIT,CLEAR,DISPLAY,SEARCH,FILTER, UNDO,REDO,UNDONE,DONE, UNDEFINED};
enum PRIORITY{HIGH,MEDIUM,LOW};
enum TIMEDATE_STATUS{EARLIER,SAME,LATER};

static const std::string CMD_TYPE_STRING[CMD_TYPE_COUNT] =	
{ "add","delete","edit","clear","display","search","filter","undefined"	};
static const std::string PRIORITY_STRING[PRIORITY_COUNT]		=		{"high","medium","low"};
static const std::string TASK_STATUS_STRING[TASK_STATUS_COUNT]	=		{"undone","overdue","done"};
static const std::string TASK_TYPE_STRING[TASK_TYPE_COUNT]		=		{"timed","deadline","floating"};

const char TASK_SPECIFIER = '#';
const char DATE_SEPARATOR = '-';

const std::string PREPOSITION[MAX_PREPOSITION] = {"at", "from", "to", "until", "on", "between", "by", "till", "before"};

const CMD_TYPE DEFAULT_COMMAND_TYPE = UNDEFINED;
const int DEFAULT_INDEX = -1;
const PRIORITY DEFAULT_PRIORITY = LOW;
const TASK_TYPE DEFAULT_TASK_TYPE = FLOATING;
const TASK_STATUS DEFAULT_TASK_STATUS = UNCOMPLETED;
const std::string DEFAULT_EMPTY = "";



#endif // !_CONSTANTS_H
